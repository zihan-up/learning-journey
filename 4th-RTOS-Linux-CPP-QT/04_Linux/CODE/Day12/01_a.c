#include <header.h>

int main(){

    /*
       int fd = open("1.pipe", O_RDONLY);

       char buf[100] = {0};
       read(fd, buf, sizeof(buf));

       printf("buf: %s \n", buf);
       */

    int fd = open("1.pipe", O_WRONLY);

    int times = 0;
    while(1){
        times++;
        char buf[4096] = {0};
        write(fd, buf, sizeof(buf));
        printf("times: %d \n", times);


    }
    return 0;
}

