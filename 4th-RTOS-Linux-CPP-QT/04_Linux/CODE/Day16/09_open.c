#include <header.h>

int main(int argc, char *argv[argc]){




    //int fd = open("1.txt", O_RDONLY);
    //size_t ret = write(fd, "nihao", 5);
    //ERROR_CHECK(ret , -1, "write");
    //close(fd);



    //int fd = open("1.txt", O_WRONLY);
    //char buf[100] = {0};
    //size_t  ret = read(fd, buf, sizeof(buf));
    //ERROR_CHECK(ret , -1, "read");
    //close(fd);



    int fd = open("1.txt", O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    write(fd, "nihao", 5);
    close(fd);
    fd = open("1.txt", O_RDWR);
    write(fd, "123", 3);
    close(fd);



    return 0;
}

