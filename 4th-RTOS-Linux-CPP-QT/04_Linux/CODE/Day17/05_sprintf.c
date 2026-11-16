#include <header.h>

int main(int argc, char *argv[argc]){


    char buf[100] = {0};
    sprintf(buf,  "%s %d", "nihao", 22);

    char str[100] = {0};
    int num = 0;
    sscanf(buf, "%s %d", str,  &num);

    printf("str:%s ;   num:%d \n", str, num);


    return 0;
}

