#include <header.h>

int main(int argc, char *argv[argc]){

    // stat: 获取文件/目录的更多元信息


    struct stat st;
    int ret = stat("./1.txt", &st);

    printf("file_size: %ld \n", st.st_size);




    return 0;
}

