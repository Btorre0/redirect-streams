// Beatriz Torres Archundia
// CPSC 351 - 08
// 10.28.2024
// btorre0@csu.fullerton.edu
// Github Username: Btorre0

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <INP> <CMD> <OUT>\n", argv[0]);
        return 1;
    }

    int inp = -1;
    if (strcmp(argv[1], "-") != 0) {
        inp = open(argv[1], O_RDONLY, 0644);
        if (inp == -1) {
            perror("open");
            return 1;
        }
    }

    int out = -1;
    if (strcmp(argv[3], "-") != 0) {
        out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out == -1) {
            perror("open");
            if (inp != -1) close(inp);
            return 1;
        }
    }

    char *cmd_args[10];
    int ix = 0;

    char *cmd = strtok(argv[2], " ");

    while (cmd && ix < 10) {
        cmd_args[ix++] = cmd;
        cmd = strtok(NULL, " ");
    }
    cmd_args[ix] = NULL;

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");

        return 1;
    } else if (pid == 0) {
        if (inp != -1) {
            if (dup2(inp, STDIN_FILENO) == -1) {
                perror("dup2 for input");
                exit(1);
            }
            close(inp);
        }

        if (out != -1) {
            if (dup2(out, STDOUT_FILENO) == -1) {
                perror("dup2 for output");
                exit(1);
            }
            close(out);
        }

        execvp(cmd_args[0], cmd_args);
        perror("execvp");
        exit(1);

    } else {
                int status;

        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Child exited with status %d\n",
                    WEXITSTATUS(status));
        } else if (!WIFEXITED(status)) {
            fprintf(stderr, "Child exited abnormally\n");
        }
    }

    return 0;
}