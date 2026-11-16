#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("1.txt", "r+");

    fwrite("hello", 1, 5, file);


    fclose(file);

    return 0;
}

