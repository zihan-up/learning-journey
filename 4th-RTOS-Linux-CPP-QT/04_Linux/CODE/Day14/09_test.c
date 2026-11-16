#include <header.h>
#include <errno.h>

int main(int argc, char *argv[argc]){

    int ret = open("1.txt", O_RDWR);
    ERROR_CHECK(ret, -1, "open");
    
    /*
    if(ret == -1){
        perror("open");
        //printf("errno: %d \n", errno);
        if(errno == EINTR){

        }
    }
    printf("ret: %d \n", ret);
    */
    
    return 0;
}

