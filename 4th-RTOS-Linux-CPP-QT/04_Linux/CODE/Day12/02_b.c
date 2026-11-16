#include <header.h>

int main(){

    int fd = open("1.txt", O_WRONLY);

    write(fd, "nihao", 5);

    close(fd);
    

    return 0;
}

