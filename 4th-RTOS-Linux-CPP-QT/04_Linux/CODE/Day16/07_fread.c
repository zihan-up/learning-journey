#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("./1.txt", "r");

    /*
    char *str = "abcdefouytrewq";
    fwrite(str, 1, strlen(str), file);
    */

    char buf[100] = {0};
    fread(buf, 1, sizeof(buf), file);

    printf("buf: %s \n", buf);

    fclose(file);
    return 0;
}

