#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR);

    write(fd, "123456789", 9);

    close(fd);

    return 0;
}

