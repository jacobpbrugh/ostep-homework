#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {

    // int totalTime {0};

    struct timeval tval1;
    struct timeval tval2;
    char buf[1];
    long totalTime = 0;
    int repCount = 1000000;

    for (int i = 0; i < repCount; ++i) {
        gettimeofday(&tval1, NULL);
        read(STDOUT_FILENO, buf, 0);
        gettimeofday(&tval2, NULL);
        totalTime += (tval2.tv_sec - tval1.tv_sec) * 1000000L + (tval2.tv_usec - tval1.tv_usec);
    }

}
