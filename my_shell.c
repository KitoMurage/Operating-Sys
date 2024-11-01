#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/* Read a line of characters from stdin. */
int getcmd(char *buf, int nbuf) {
    fprintf(1, ">>> ");
    memset(buf, 0, nbuf);
    gets(buf, nbuf);

    // Remove leading white space
    int i = 0;
    while (buf[i] == ' ' || buf[i] == '\t') {
        i++;
    }
    if (i > 0) {
        memmove(buf, &buf[i], strlen(buf) - i + 1);
    }

    // Remove trailing white space
    int len = strlen(buf);
    while (len > 0 && (buf[len - 1] == ' ' || buf[len - 1] == '\t' || buf[len - 1] == '\n')) {
        len--;
    }
    buf[len] = '\0';

    // Remove extra spaces between
    int j = 0;
    for (i = 0; i < len; i++) {
        if (buf[i] != ' ' && buf[i] != '\t') {
            buf[j++] = buf[i];
        } else if (j > 0 && buf[j - 1] != ' ') {
            buf[j++] = ' ';
        }
    }
    buf[j] = '\0';

    if (strlen(buf) == 0) {
        return -1; // Return -1 for empty input
    }
    return 0; // Successful read
}

/*
  A recursive function which parses the command
  at *buf and executes it.
*/
__attribute__((noreturn))
void run_command(char *buf, int nbuf, int *pcp) {
    /* Useful data structures and flags. */
    char *arguments[10];
    int numargs = 0;
    /* Word start/end */
    int ws = 1;

    int redirection_left = 0;
    int redirection_right = 0;
    char *file_name_l = 0;
    char *file_name_r = 0;

    int p[2]; // For pipe
    int pipe_cmd = 0;

    int sequence_cmd = 0;

    int i = 0;
    /* Parse the command character by character. */
    for (; i < nbuf; i++) {
        char c = buf[i];
        /* Parse the current character and set-up various flags:
           sequence_cmd, redirection, pipe_cmd and similar. */

        if (c == ';') {
            sequence_cmd = 1;
            buf[i] = '\0'; // Null-terminate the command
            continue;
        }

        /* No redirection, continue parsing command. */
        if (!(redirection_left || redirection_right)) {
            if (c == '<') {
                redirection_left = 1;
                buf[i] = '\0';
                file_name_l = &buf[i + 1];
                while (*file_name_l == ' ') file_name_l++;
                continue;
            }
            if (c == '>') {
                redirection_right = 1;
                buf[i] = '\0';
                file_name_r = &buf[i + 1];
                while (*file_name_r == ' ') file_name_r++;
                continue;
            }
            if (c == '|') {
                pipe_cmd = 1;
                buf[i] = '\0';
                continue;
            }
            if (ws) {
                arguments[numargs++] = &buf[i];
                ws = 0;
            } else {
                buf[i] = '\0'; // Null-terminate the current argument
            }
        } else {
            /* Redirection command. Capture the file names. */
            // (Handled above)
        }
    }

    /*
      Sequence command. Continue this command in a new process.
      Wait for it to complete and execute the command following ';'.
    */
    if (sequence_cmd) {
        sequence_cmd = 0;
        if (fork() != 0) {
            wait(0); // Wait for child
            return; // Return to continue reading commands
        } else {
            arguments[numargs] = 0; // Null-terminate arguments
            exec(arguments[0], arguments);
            fprintf(2, "Command failed\n");
            exit(1);
        }
    }

    /*
      If this is a redirection command,
      tie the specified files to std in/out.
    */
    if (redirection_left) {
        int fd = open(file_name_l, O_RDONLY);
        if (fd < 0) {
            fprintf(2, "Error opening input file\n");
            exit(1);
        }
        dup(fd);
        close(fd);
    }

    if (redirection_right) {
        int fd = open(file_name_r, O_WRONLY | O_CREATE);
        if (fd < 0) {
            fprintf(2, "Error opening output file\n");
            exit(1);
        }
        dup(fd);
        close(fd);
    }

    /* Parsing done. Execute the command. */
    arguments[numargs] = 0; // Null-terminate arguments

    /*
      If this command is a CD command, write the arguments to the pcp pipe
      and exit with '2' to tell the parent process about this.
    */
    if (strcmp(arguments[0], "cd") == 0) {
        if (numargs < 2 || chdir(arguments[1]) < 0) {
            fprintf(2, "cd failed\n");
        }
        exit(0); // Exit after cd
    } else {
        /*
          Pipe command: fork twice. Execute the left hand side directly.
          Call run_command recursion for the right side of the pipe.
        */
        if (pipe_cmd) {
            pipe(p);
            if (fork() == 0) {
                dup(p[1]); // Redirect stdout to the pipe
                close(p[0]); // Close read end of pipe
                exec(arguments[0], arguments); // Execute left command
                fprintf(2, "Command failed\n");
                exit(1);
            }
            if (fork() == 0) {
                dup(p[0]); // Redirect stdin to the pipe
                close(p[1]); // Close write end of pipe
                run_command(&buf[i + 1], nbuf - i - 1, pcp); // Recursive call for right command
                fprintf(2, "Command failed\n");
                exit(1);
            }
            close(p[0]);
            close(p[1]);
            wait(0);
            wait(0);
            exit(0);
        } else {
            exec(arguments[0], arguments);
            fprintf(2, "Command failed\n");
            exit(1);
        }
    }
}

int main(void) {
    static char buf[100];

    int pcp[2];
    pipe(pcp);

    /* Read and run input commands. */
    while (getcmd(buf, sizeof(buf)) >= 0) {
        if (fork() == 0) {
            run_command(buf, sizeof(buf), pcp);
        }

        /*
          Check if run_command found this is
          a CD command and run it if required.
        */
        int child_status;
        wait(&child_status);
        if (child_status == 2) {
            continue; // If it's a cd command, continue the loop
        }
    }
    exit(0);
}
