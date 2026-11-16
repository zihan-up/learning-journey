#include <header.h>

int main(){

    /*
    char buf[100] = {0};
    read(0, buf, sizeof(buf));
    printf("buf: %s \n", buf);
    */

    /*
    char *str = "nihao1234567890";
    write(1, str, 15);
    */


    char *str = "nihao1234567890";
    write(STDOUT_FILENO, str, 15);

    return 0;
}

