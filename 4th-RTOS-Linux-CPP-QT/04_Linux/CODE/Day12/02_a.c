#include <header.h>

int main(){

    int fd = open("1.txt", O_RDONLY);
    
    char buf[100] = {0};
    read(fd, buf, sizeof(buf));

    printf("buf: %s \n", buf);

    return 0;
}

