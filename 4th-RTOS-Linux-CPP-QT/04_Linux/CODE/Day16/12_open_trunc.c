#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR | O_TRUNC);

    close(fd);
    return 0;
}

