#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR);

    ssize_t ret = write(fd, "hello", 5);

    printf("%ld ", ret);

    return 0;
}

