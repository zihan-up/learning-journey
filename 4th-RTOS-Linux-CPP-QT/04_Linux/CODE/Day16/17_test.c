#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("2.txt", O_RDWR);

    /*
    int num = 100;
    write(fd, &num, sizeof(int));
    */

    int num = 0;
    read(fd, &num, sizeof(int));


    printf("num: %d \n", num);


    close(fd);
    return 0;
}

