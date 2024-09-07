#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

const int BUFFER_SIZE = 1024;

int main() {

    int fd;
    pid_t pid;
    const char *string;
    ssize_t bytesRead;
    char buffer[BUFFER_SIZE];
    char *fileContent = NULL;
    size_t fileSize = 0;

    fd = open("/tmp/fork", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    pid = fork();


    if (pid == 0) {
        string = "Hello from child";
    } else {
        string = "Hello from parent";
    }
    ssize_t bytes_written = write(fd, string, strlen(string));

    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }


    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (bytesRead == -1) {
            perror("read");
            free(fileContent);
            close(fd);
            return 1;
        }

        fileContent = realloc(fileContent, fileSize + (size_t)bytesRead + 1);
        if (fileContent == NULL) {
            perror("realloc");
            close(fd);
            return 1;
        }

        memcpy(fileContent + fileSize, buffer, bytesRead);
        fileSize += (size_t)bytesRead;
    }


    fileContent[fileSize] = '\0';
    printf("File content:\n%s\n", fileContent);

    free(fileContent);
    close(fd);

    return 0;
}
