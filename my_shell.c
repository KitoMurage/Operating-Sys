#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/* Read a line of characters from stdin. */
int getcmd(char *buf, int nbuf) {
    fprintf(1, ">>> ");
    memset(buf, 0, nbuf);
    if (gets(buf, nbuf) == 0){
      fprintf(2, "error\n");
      return -1;
     }

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

    // Remove space between
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
        fprintf(2, "Error: empty command\n");
        return -1;
    }
    return 0;
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
    int we = 0;

    int redirection_left = 0;
    int redirection_right = 0;
    char *file_name_l = 0;
    char *file_name_r = 0;

    int pipe_cmd = 0;

    int sequence_cmd = 0;

    int i = 0;

    /* Parse the command character by character. */
    for (; i < nbuf; i++) {
        char c = buf[i];
        /* Parse the current character and set-up various flags:
           sequence_cmd, redirection, pipe_cmd and similar.*/ 
        /* ##### Place your code here. */
        if(c == '\0' || c == '\n'){
          if (!ws) {
            buf[i] = '\0';
            arguments[numargs++] = &buf[we];
           }
          break;
        }
	if (!(redirection_left || redirection_right)) {
            /* No redirection, continue parsing command. */
              switch (c) {
                case ';':
                    buf[i] = '\0';
                    sequence_cmd = 1;
                    break;

                case '|':
                    buf[i] = '\0';
                    pipe_cmd = 1;
                    break;

                case '<':
                    redirection_left = 1;
                    buf[i] = '\0';
                    file_name_l = &buf[i + 1];
                    break;

                case '>':
                    redirection_right = 1;
                    buf[i] = '\0';
                    file_name_r = &buf[i + 1];
                    break;

                case '\0':
                    if (!ws) {
                        buf[i] = '\0';
                        arguments[numargs++] = &buf[we];
                    }
                    break;

                default:
                    if (c != ' ' && c != '\t' && c != '\n') {
                        if (ws) {
                            ws = 0;
                            we = i;
                        }
                    } else {
                        if (!ws) {
                            buf[i] = '\0';
                            arguments[numargs++] = &buf[we];
                            ws = 1;
                        }
                    }
                    break;
            }
} else {
            /* Redirection command. Capture the file names. */
            if (c == '<') {
                fprintf(1, "Detected left redirection\n");
                redirection_left = 1;
                buf[i] = '\0';
                file_name_l = &buf[i + 1];
            } else if (c == '>') {
                fprintf(1, "Detected right redirection\n");
                redirection_right = 1;
                buf[i] = '\0';
                file_name_r = &buf[i + 1];
            }
	}
    }
/*    if(numargs > 0){
      for(int k=0; k < numargs; k++){
        fprintf(1, "Arg[%d]: %s\n", k, arguments[k]);
      }
    }else{
        fprintf(1, "No Args\n");
    }*/
    /*
      Sequence command. Continue this command in a new process.
      Wait for it to complete and execute the command following ';'.
    */
if (sequence_cmd) {
        sequence_cmd = 0;
        if (fork() != 0) {
            wait(0);
            // ##### Place your code here.
            // Possibly handle the next command after the ';' here
        } else {
            exec(arguments[0], arguments);
            fprintf(2, "Sequence command execution failed\n");
            exit(1);
        }
    }

    /*
      If this is a redirection command,
      tie the specified files to std in/out.
    */


    if (redirection_left) {
        // ##### Place your code here.
        int fd = open(file_name_l, O_RDONLY);
        if (fd < 0) {
            fprintf(2, "Error opening input file: %s\n", file_name_l);
            exit(1);
        }
	close(0); // Close stdin
        dup(fd);  // Redirect stdin to the file
        close(fd); // Close original file descriptor
    }

    if (redirection_right) {
        // ##### Place your code here.
        int fd = open(file_name_r, O_WRONLY | O_CREATE);
        if (fd < 0) {
            fprintf(2, "Error opening output file: %s\n", file_name_r);
            exit(1);
        }
	close(1); // Close stdout
        dup(fd);  // Redirect stdout to the file
        close(fd); // Close original file descriptor
    }

    /* Parsing done. Execute the command. */
    
   /* if this command is a CD command, write arguments to the pcp pipe
   and exit with '2' to tell the parent process about this*/


    if (numargs> 0 && strcmp(arguments[0], "cd") == 0) {
        if(numargs < 2){
          fprintf(2, "cd: no such file or directory\n");
         }else{
            write(pcp[1], arguments[1], strlen(arguments[1]) + 1);
            fprintf(1, "changed dir to : %s\n", arguments[1]);
}

         exit(2);
} else {
	/*
          Pipe command: fork twice. Execute the left hand side directly.
          Call run_command recursion for the right side of the pipe.
        */

	if (pipe_cmd) {
            // ##### Place your code here.
            int p[2];
            pipe(p);
            if (fork() == 0) {
		close(1); 
                dup(p[1]); 
                close(p[0]);
                close(p[1]);
                exec(arguments[0], arguments);
                printf("exec %s failed\n", arguments[0]);
                exit(1);
            }

            if (fork() == 0) {

                //close(p[1]);
                close(0);
                dup(p[0]);
                close(p[0]);
                close(p[1]);
                run_command(&buf[i + 1], nbuf - i + 1, pcp);
            }

            close(p[0]);
            close(p[1]);
            wait(0);
            wait(0);

            } else {
            // ##### Place your code here.
          //  arguments[numargs] = 0;
            exec(arguments[0], arguments);
            printf("exec %s failed\n", arguments[0]);
        }
    }
    exit(0);
}

int main(void) {
    static char buf[100];

    int pcp[2];
    pipe(pcp);

    /* Read and run input commands. */
    while (getcmd(buf, sizeof(buf)) >= 0) {
        if (fork() == 0) {
            run_command(buf, 100, pcp);
        }

	/*
          Check if run_command found this is
          a CD command and run it if required.
        */
	int child_status;
        wait(&child_status);
        if (child_status == 2){
          char new_dir[100];
          if(read(pcp[0], new_dir, sizeof(new_dir)) > 0){
            if(chdir(new_dir) < 0){
              fprintf(2, "failed\n");}
          }
	}
    }
    exit(0);
}
