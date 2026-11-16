#include <header.h>

int main(int argc, char *argv[argc]){


    //int fd = open("/home/snow/code/4th/04_Linux/CODE/Day16/1.txt", O_RDWR);
    int fd = open("1.txt", O_RDWR);
    // int fd = open("../Day16/1.txt", O_RDWR);// 

    ERROR_CHECK(fd, -1, "open");

    char buf[100] = {0};
    read(fd, buf, sizeof(buf));

    printf("%s\n", buf);


    close(fd);
    return 0;
}

