#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main() {

    pid_t pid = fork();
    pid_t wait_pid;
    int wstatus;

    if (pid == 0) {
        printf("hello\n");
    } else {
        do {
            wait_pid = waitpid(pid, &wstatus, 0);
        } while (wait_pid == -1 && errno == EINTR);
        if (wait_pid == -1) {
            printf("wait failed with errno: %d\n", errno);
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));

        } else {
            printf("goodbye\n");
            printf("pid %d\n", pid);
            printf("waitpid %d\n", wait_pid);
        }

    }
}
