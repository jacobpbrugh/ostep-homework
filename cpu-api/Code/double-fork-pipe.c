#include <unistd.h>
#include <stdio.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        printf("From proc1\n");
    } else {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            printf("From proc2\n");
            char line[256];

            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            if (fgets(line, sizeof(line), stdin)) {
                printf("Read from proc1: %s", line);
            } else {
                printf("Error reading input.\n");
            }
        }
    }
}
