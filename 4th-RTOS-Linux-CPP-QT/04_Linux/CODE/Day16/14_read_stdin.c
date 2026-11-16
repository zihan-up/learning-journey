#include <header.h>

int main(int argc, char *argv[argc]){

    //int fd = open("1.txt", O_RDWR);
    //char buf[100] = {0};
    //read(fd, buf, sizeof(buf));


    char buf[100] = {0};
    read(0, buf, sizeof(buf));
    //read(STDIN_FILENO, buf, sizeof(buf));



    printf("buf: %s \n", buf);

    return 0;
}

