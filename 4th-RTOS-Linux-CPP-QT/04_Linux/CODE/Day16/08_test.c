#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("./1.txt", "w+");

    int num = file->_fileno;
    printf("num: %d \n", num);

    write(3, "aaaaa", 5);



    fclose(file);
    return 0;
}

