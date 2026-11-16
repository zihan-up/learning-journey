#include <header.h>

int main(int argc, char *argv[argc]){

    int fd1  = open("1.txt", O_RDWR);
    printf("fd1: %d \n", fd1);

    int fd2 = open("./01_opendir", O_RDWR);
    printf("fd2: %d \n", fd2);

    close(fd1);

    int fd3 = open("./Makefile", O_RDWR);
    printf("fd3: %d \n", fd3);

    return 0;
}

