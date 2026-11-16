#include <header.h>

int main(int argc, char *argv[argc]){


    int fd = open("1.txt", O_RDWR);

    ftruncate(fd, 10000000);


    close(fd);


    return 0;
}

