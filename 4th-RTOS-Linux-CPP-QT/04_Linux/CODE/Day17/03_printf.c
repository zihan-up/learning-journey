#include <header.h>

int main(int argc, char *argv[argc]){

    printf("123 \n");

    char buf[100] = {0};
    sprintf(buf,  "%s", "nihao");


    FILE *file = fopen("1.txt", "r+");
    fprintf(file, "%s  %d ", "zs", 10);

    fprintf(stdout, "%s   %s", "123", "456");

    return 0;
}

