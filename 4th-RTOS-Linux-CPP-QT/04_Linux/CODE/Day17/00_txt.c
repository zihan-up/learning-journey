#include <header.h>

int main(int argc, char *argv[argc]){


    int fd = open("1.txt", O_RDWR|O_CREAT, 0666);

    write(fd, "hello", 5);

    char buf[100] = {0};
    read(fd, buf, sizeof(buf));
    printf("%s \n", buf);

    close(fd);
    return 0;
}

