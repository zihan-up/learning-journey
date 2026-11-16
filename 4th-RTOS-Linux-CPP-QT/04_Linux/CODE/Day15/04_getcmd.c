#include <header.h>

int main(int argc, char *argv[argc]){

    char buf[200] = {0};
    char *str = getcwd(NULL, sizeof(buf));
    //char *str = getcwd(buf, sizeof(buf));

    printf("buf: --%s-- \n", buf);
    printf("str: --%s-- \n", str);

    if(str == buf){
        printf("if \n");
    }else{
        free(str);
    }


    return 0;
}

