#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/* Read a line of characters from stdin. */
int getcmd(char *buf, int nbuf) {
    printf(">>> ");  // Display the prompt
    int i = 0;
    char c;
    while (i < nbuf - 1) {
        if (read(0, &c, 1) != 1)  // Read one byte from stdin
            break;
        if (c == '\n')  // If a newline is encountered, stop
            break;
        buf[i++] = c;
    }
    buf[i] = '\0';  // Null terminate the string
    return i;
}

/*
  A recursive function which parses the command
  at *buf and executes it.
*/
__attribute__((noreturn))
void run_command(char *buf, int nbuf, int *pcp) {

    char *arguments[10];
    int numargs = 0;
	
    int ws = 1;
    int we = 0;
	
    int redirection_left = 0;
    int redirection_right = 0;
	
    char *file_name_l = 0;
    char *file_name_r = 0;
	
    int p[2];
    int pipe_cmd = 0;
	
    int sequence_cmd = 0;
   
    int i = 0;
    /* Parse command character by character */
    for (; i < nbuf; i++) {
        char c = buf[i];

        if (c == '\0' || c == '\n') {
            if (!ws) {
                buf[i] = '\0';
                arguments[numargs++] = &buf[we];
                ws = 1;
            }
            break;
        }

	if (c == '<') {
            redirection_left = 1;
            buf[i] = '\0';
            while (buf[i + 1] == ' ' || buf[i + 1] == '\t') i++;
            file_name_l = &buf[i + 1];
            continue;
        } else if (c == '>') {
            redirection_right = 1;
            buf[i] = '\0';
            while (buf[i + 1] == ' ' || buf[i + 1] == '\t') i++;
            file_name_r = &buf[i + 1];
            continue;
        }

	if (!redirection_left && !redirection_right) {
            switch (c) {
                case ';':
                    buf[i] = '\0';
                    sequence_cmd = 1;
                    break;
                case '|':
                    buf[i] = '\0';
                    pipe_cmd = 1;
                    break;
                default:
                    if (c != ' ' && c != '\t') {
                        if (ws) { ws = 0; we = i; }
                    } else if (!ws) {
                        buf[i] = '\0';
                        arguments[numargs++] = &buf[we];
                        ws = 1;
                    }
                    break;
            }
	}
    }

    if (sequence_cmd) {
        sequence_cmd = 0;
        if (fork() != 0) {
            wait(0);}
        else{
          exec(arguments[0], arguments);
          fprintf(2, "sequence failed\n");
          exit(1);
            //run_command(&buf[we + 1], nbuf - we - 1, pcp);
        }
    }

    if (redirection_left) {
        int fd = open(file_name_l, O_RDONLY);
        if (fd < 0) {
            fprintf(2, "Error opening input file: %s\n", file_name_l);
            exit(1);
        }
	close(0);
        dup(fd);
        close(fd);
    }
    if (redirection_right) {
        int fd = open(file_name_r, O_WRONLY | O_CREATE);
        if (fd < 0) {
            fprintf(2, "Error opening output file: %s\n", file_name_r);
            exit(1);
        }
	close(1);
        dup(fd);
        close(fd);
    }

    if (numargs > 0 && strcmp(arguments[0], "cd") == 0) {
        if (numargs < 2) {
            fprintf(2, "cd: no directory specified\n");
        } else {
            write(pcp[1], arguments[1], strlen(arguments[1]) + 1);
            exit(2);
        }
    } else if (pipe_cmd) {
        
        pipe(p);
        if (fork() == 0) {
            close(p[0]);
            dup(p[1]);
            //close(p[0]);
            close(p[1]);
            exec(arguments[0], arguments);
            fprintf(2, "Execution of left pipe failed\n");
            exit(1);
        }
	if (fork() == 0) {
            close(p[1]);
            dup(p[0]);
            close(p[0]);
            
            run_command(buf + numargs + 1, nbuf - numargs - 1, pcp);
           
            fprintf(2, "Execution of right pipe failed\n");
            exit(1);

        }
	close(p[0]);
        close(p[1]);
        wait(0);
        wait(0);
    } else {
	arguments[numargs] = 0;
        exec(arguments[0], arguments);
        fprintf(2, "Execution of %s failed\n", arguments[0]);

    }
    exit(1);
}

int main(void) {
    static char buf[100];
    int pcp[2];
    pipe(pcp);

    while (getcmd(buf, sizeof(buf)) >= 0) {
        if (fork() == 0) {
            run_command(buf, 100, pcp);
        }
	int child_status;
        wait(&child_status);
        if (child_status == 2) {
            char new_dir[100];
            if (read(pcp[0], new_dir, sizeof(new_dir)) > 0) {
                if (chdir(new_dir) < 0) {
                    fprintf(2, "chdir to %s failed\n", new_dir);
                }
            }
	}
    }
    exit(0);
}
