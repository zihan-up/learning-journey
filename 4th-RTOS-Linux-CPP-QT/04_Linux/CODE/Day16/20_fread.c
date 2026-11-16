#include <header.h>

int main(int argc, char *argv[argc]){

    /*
    FILE *file = fopen("1.txt", "r+");
    char buf[100] = {0};
    fread(buf, 1, sizeof(buf), file);
    printf("buf: %s \n", buf);
    fclose(file);
    */


    char buf[100] = {0};
    fread(buf, 1, 10, stdin);
    printf("buf: %s \n", buf);



    return 0;
}

