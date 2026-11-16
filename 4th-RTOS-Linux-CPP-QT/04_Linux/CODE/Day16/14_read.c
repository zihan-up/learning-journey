#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR);


    char buf[100] = {0};
    read(fd, buf, sizeof(buf));
    printf("buf: ---%s--- \n ", buf);


    /*
    char buf[2] = {0};
    read(fd,  buf,  sizeof(buf));
    printf("-%s-\n", buf);

    memset(buf, 0, sizeof(buf));
    read(fd,  buf,  sizeof(buf));
    printf("-%s-\n", buf);

    memset(buf, 0, sizeof(buf));
    read(fd,  buf,  sizeof(buf));
    printf("-%s-\n", buf);

    */


    close(fd);
    return 0;
}

