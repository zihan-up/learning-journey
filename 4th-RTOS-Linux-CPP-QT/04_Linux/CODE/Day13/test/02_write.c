#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR);

    char *str = "10";
    write(fd, str, strlen(str));


    int fd2 = open("2.txt", O_RDWR);
    int num = 10;
    write(fd2, &num, sizeof(int));


    return 0;
}

