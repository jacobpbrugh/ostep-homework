#include <unistd.h>    // For fork(), getpid(), and getppid()
#include <stdio.h>

int main() {
    int x = 100;
    int rc = fork();

    printf("Hello, world! x = %d\n", x);

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        return 1;
    } else if (rc == 0) {
        printf("Hello, I am child! x = %d\n", x);
        x += 50;
    } else {
        printf("Hello, I am parent of %d! x = %d\n", rc, x);
        x += 25;
    }

    printf("Hello, again! x = %d\n", x);
}
