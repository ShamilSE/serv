#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv, char** env) {
    for (size_t index = 0; env[index]; index++) {
        printf("%s\n", env[index]);
    }
    return 0;
}
