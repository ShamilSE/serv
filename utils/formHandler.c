#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv, char** env) {
    int filefd = open("newfile", O_CREAT | O_RDWR | O_TRUNC, 777);
    if (filefd < 0)
        printf("cannot open file\n");

    for (size_t index = 0; env[index]; index++) {
        write(filefd, env[index], strlen(env[index]));
        write(filefd, "\n", 1);
    }
    close(filefd);
    return 0;
}
