#include <header.h>

int main(){

    int fd = open("1.txt", O_RDWR);

    ftruncate(fd, 10000000);

    return 0;
}

