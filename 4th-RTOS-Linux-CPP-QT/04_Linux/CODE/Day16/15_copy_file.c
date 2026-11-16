#include <header.h>

int main(int argc, char *argv[argc]){

    int fd1 = open("1.txt", O_RDWR);

    int fd2 = open("2.txt", O_RDWR|O_CREAT, 0666);

    
    /*
    char buf[100] = {0};
    ssize_t ret = read(fd1, buf, sizeof(buf));
    write(fd2, buf, ret);
    */

     
    while(1){
        char buf[1] = {0};
        ssize_t ret = read(fd1, buf, sizeof(buf));
        if(ret == 0){
            break;
        }
        write(fd2, buf, ret);
    }


    close(fd1);
    close(fd2);
    return 0;
}

