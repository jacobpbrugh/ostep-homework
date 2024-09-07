#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    const char *const env[] = {
        "TEST_ENV=1",
        NULL
    };
    const char *const args[] = {
        "/usr/bin/env",
        NULL
    };
    if (pid == 0) {
        int ret = execve("/usr/bin/env", (char *const *)args, (char *const *)env);

        if (ret != 0) {
            perror("error execing env");
        }
    }
}
