#include <header.h>

int main(int argc, char *argv[argc]){

    char buf[200] = {0};
    getcwd(buf, sizeof(buf));
    printf("pwd: %s \n", buf);

    int ret = chdir("./test");
    ERROR_CHECK(ret, -1, "chdir");


    bzero(buf, sizeof(buf));
    getcwd(buf, sizeof(buf));
    printf("pwd: %s \n", buf);

    mkdir("./test2", 0777);

    while(1){}
    return 0;
}

