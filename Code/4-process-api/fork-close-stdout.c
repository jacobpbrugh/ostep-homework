#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(){
    pid_t pid = fork();

    if (pid == 0) {
        close(STDOUT_FILENO);
        printf("what happens?");
    } else {
        int wstatus;
        wait(&wstatus);
        printf("printing from parent");
        printf("child returend %d", WEXITSTATUS(wstatus));
    }
}
