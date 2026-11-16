#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("1.txt", "r+");

    /*
    while(1){
        int ch = fgetc(file);
        if(ch == EOF){
            break;
        }
        printf("%c", ch );
    }
    printf(" \n");
    */

    char *str = "123456789";

    for(int i=0; i<strlen(str); i++){
        fputc(str[i], file);
    }



    fclose(file);
    return 0;
}

