#include <header.h>

int main(int argc, char *argv[argc]){

    FILE *file = fopen("1.txt", "r+");
    // file->_fileno:  FILE对象的文件描述符下标 


    //read(文件描述符,  存储地址,  读取的数据字节数);
    //fread(存储地址, 单个数据的大小,   数据个数,   FILE对象的指针);

    char buf[100] = {0};
    size_t ret = fread(buf, 1, sizeof(buf), file);
    printf("ret: %ld ; buf: %s \n", ret, buf);


    fclose(file);
    return 0;
}

