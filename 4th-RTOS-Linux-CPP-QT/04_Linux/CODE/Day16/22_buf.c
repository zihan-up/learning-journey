#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("1.txt", "r+");


    fwrite("nihao", 1, 5, file);


    fflush(file);
    while(1){
        printf("while \n");
        sleep(1);
    }

    fclose(file);
    return 0;
}

