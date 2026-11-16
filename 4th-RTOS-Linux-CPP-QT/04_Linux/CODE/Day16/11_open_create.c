#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR |O_CREAT  , 0666);

    write(fd, "abc", 3);

    close(fd);

    return 0;
}

