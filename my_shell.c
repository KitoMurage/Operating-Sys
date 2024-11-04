#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/* Read a line of characters from stdin. */
int getcmd(char *buf, int nbuf) {
    fprintf(1, ">>> ");
    memset(buf, 0, nbuf);
    if (gets(buf, nbuf) == 0) {
        fprintf(2, "error\n");
        return -1;
    }

    // Trim leading whitespace
    int i = 0;
    while (buf[i] == ' ' || buf[i] == '\t') {
        i++;
    }
    if (i > 0) {
        memmove(buf, &buf[i], strlen(buf) - i + 1);
    }

    // Trim trailing whitespace
    int len = strlen(buf);
    while (len > 0 && (buf[len - 1] == ' ' || buf[len - 1] == '\t' || buf[len - 1] == '\n')) {
        len--;
    }
    buf[len] = '\0';

    // Compact spaces between words
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
  A recursive function which parses the command at *buf and executes it.
*/
__attribute__((noreturn))
void run_command(char *buf, int nbuf, int *pcp) {
    char *arguments[10];
    int numargs = 0;
    int redirection_left = 0, redirection_right = 0;
    char *file_name_l = 0, *file_name_r = 0;
    int pipe_cmd = 0, sequence_cmd = 0;
    int ws = 1, we = 0;
    int p[2];

    // Parse command
    for (int i = 0; i < nbuf; i++) {
        char c = buf[i];
        if (c == '\0' || c == '\n') {
            if (!ws) {
                buf[i] = '\0';
                arguments[numargs++] = &buf[we];
            }
            break;
        }
        
        if (!(redirection_left || redirection_right)) {
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
                default:
                    if (c != ' ' && c != '\t' && c != '\n') {
                        if (ws) {
                            ws = 0;
                            we = i;
                        }
                    } else if (!ws) {
                        buf[i] = '\0';
                        arguments[numargs++] = &buf[we];
                        ws = 1;
                    }
                    break;
            }
        }
    }
    
    arguments[numargs] = 0; // Null-terminate the arguments for exec

    if (sequence_cmd) {
        sequence_cmd = 0;
        if (fork() == 0) {
            exec(arguments[0], arguments);
            fprintf(2, "Sequence command execution failed\n");
            exit(1);
        } else {
            wait(0);
            run_command(&buf[strlen(arguments[0]) + 1], nbuf - strlen(arguments[0]) - 1, pcp);
        }
    }

    if (redirection_left) {
        int fd = open(file_name_l, O_RDONLY);
        if (fd < 0) {
            fprintf(2, "Error opening input file: %s\n", file_name_l);
            exit(1);
        }
        close(0); dup(fd); close(fd);
    }

    if (redirection_right) {
        int fd = open(file_name_r, O_WRONLY | O_CREATE);
        if (fd < 0) {
            fprintf(2, "Error opening output file: %s\n", file_name_r);
            exit(1);
        }
        close(1); dup(fd); close(fd);
    }

    if (numargs > 0 && strcmp(arguments[0], "cd") == 0) {
        if (numargs < 2 || chdir(arguments[1]) < 0) {
            fprintf(2, "cd: no such file or directory\n");
        }
        exit(2);
    } else if (pipe_cmd) {
        pipe(p);
        if (fork() == 0) {
            close(1); dup(p[1]); close(p[0]); close(p[1]);
            exec(arguments[0], arguments);
            fprintf(2, "Pipe left exec failed\n");
            exit(1);
        }

        if (fork() == 0) {
            close(0); dup(p[0]); close(p[0]); close(p[1]);
            run_command(&buf[strlen(arguments[0]) + 1], nbuf - strlen(arguments[0]) - 1, pcp);
        }

        close(p[0]); close(p[1]);
        wait(0); wait(0);
    } else {
        exec(arguments[0], arguments);
        fprintf(2, "exec %s failed\n", arguments[0]);
    }
    exit(0);
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
            if (read(pcp[0], new_dir, sizeof(new_dir)) > 0 && chdir(new_dir) < 0) {
                fprintf(2, "failed\n");
            }
        }
    }
    exit(0);
}
