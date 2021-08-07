#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("formHandler without arguments\n");
        exit(1);
    }
    printf("user's name is %s\n", argv[1]);
    printf("user's last name is %s\n", argv[2]);
    return 0;
}
