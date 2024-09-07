
#include <unistd.h>
#include <stdio.h>

int main() {

    int pipefd[2];

    pipe(pipefd);

    pid_t pid = fork();

    if (pid == 0) {
        printf("hello");
        write(pipefd[1], "done", 4);
    } else {
        char buf[4];
        read(pipefd[0], buf, sizeof(buf));
        printf("goodbye");
    }
}
