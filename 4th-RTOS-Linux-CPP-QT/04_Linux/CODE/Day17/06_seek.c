#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("1.txt", "r+");

    char *str = "123456789qwert";
    fwrite(str, 1, strlen(str), file);

    // 移动偏移位置
    //fseek(file, 2, SEEK_SET);
    fseek(file, -2, SEEK_END);
    fseek(file, -2, SEEK_END);
    //fseek(file, -2, SEEK_CUR);
    //fseek(file, -2, SEEK_CUR);

    char buf[100] = {0};
    fread(buf, 1,  sizeof(buf), file);
    printf("buf: %s \n", buf);

    fclose(file);
    return 0;
}

