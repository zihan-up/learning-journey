#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR);

    int fd2 = open("2.txt", O_RDWR);

    char buf[10] = {0};
    int num = 0;


    read(fd, buf, sizeof(buf));
    read(fd2, &num, sizeof(int));


    printf("num: %s \n", buf);
    printf("num: %d \n", num);

    return 0;
}

