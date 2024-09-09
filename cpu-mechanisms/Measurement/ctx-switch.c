#include <stdio.h>
#include <sched.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();

    char buf[1] = {'\n'};
    struct timeval tval1;
    struct timeval tval2;
    long totalTime = 0;

    int repCount = 1000000;
    for (int i = 0; i < repCount; i++) {
        if (pid == 0) {
            write(pipefd[0], buf, 1);
            gettimeofday(&tval1, NULL);
            read(pipefd[0], buf, 1);
            gettimeofday(&tval2, NULL);
            totalTime += (tval2.tv_sec - tval1.tv_sec) * 1000000L + (tval2.tv_usec - tval1.tv_usec);
        } else {
            read(pipefd[1], buf, 1);
            write(pipefd[1], buf, 1);
        }
    }

    if (pid == 0) {
        printf("total elapsed: %ld\n", totalTime);
        printf("avg telapsed: %f\n", (double)totalTime / (4 * repCount));
    }
}
