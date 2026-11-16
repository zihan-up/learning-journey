#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file1 = fopen("1.txt", "r+");
    FILE *file2 = fopen("2.txt", "r+");

    while(1){
        char buf[1024] = {0};
        char * ret = fgets(buf, sizeof(buf), file1); 
        if(ret == NULL){
            break;
        }
        fputs(buf, file2);

        printf("%s", buf);

    }

    fclose(file1);
    fclose(file2);
    return 0;
}

