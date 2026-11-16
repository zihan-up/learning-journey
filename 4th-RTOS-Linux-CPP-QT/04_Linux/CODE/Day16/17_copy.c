#include <header.h>

int main(int argc, char *argv[argc]){

    int fd1 =  open("1.txt", O_RDWR);
    int fd2 = open("2.txt", O_RDWR|O_CREAT, 0666);


    /*
    int num = 0;
    read(fd1, &num, sizeof(int));
    write(fd2, &num, sizeof(int));
    */

    char buf[100] = {0};
    ssize_t  ret = read(fd1, buf, sizeof(buf));
    printf("buf: %s \n", buf);
    write(fd2, buf, ret);


    close(fd1);
    close(fd2);

    return 0;
}

