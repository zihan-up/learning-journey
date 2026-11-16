#include <header.h>

int main(){

    int fd = open("1.pipe", O_RDONLY);

    //sleep(100000);

    while(1){
        sleep(2);
        char buf[1024] = {0};
        read(fd, buf, sizeof(buf));
        printf("read \n");
    }

    close(fd);
    

    return 0;
}

