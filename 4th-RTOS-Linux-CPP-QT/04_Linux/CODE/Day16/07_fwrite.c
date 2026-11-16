#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("./1.txt", "w+");

    char *str = "abcdefouytrewq";

    fwrite(str, 1, strlen(str), file);

    fclose(file);
    return 0;
}

