#include <header.h>

int main(int argc, char *argv[argc]){


    FILE *file = fopen("1.txt", "r+");
    fprintf(file, "%s  %d ", "zs", 10);
    fclose(file);

    // -------------------------------
    char buf[100] = {0};
    int num = 0;

    FILE *file2 = fopen("1.txt", "r+");
    fscanf(file2, "%s  %d ", buf, &num);
    fclose(file);

    printf("buf:%s ;  num:%d \n", buf, num);
    return 0;
}

