#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR);

    int times = 0;
    while(1){
          times++;
          char buf[10] = {0};
          sprintf(buf, "%daaa", times);

          write(fd, buf,  strlen(buf));

          sleep(1);
    }

    close(fd);
    return 0;
}

