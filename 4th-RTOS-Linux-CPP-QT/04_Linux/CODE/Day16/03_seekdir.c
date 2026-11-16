#include <header.h>

int main(int argc, char *argv[argc]){

    DIR *dir = opendir("./test");

    // telldir: 记录目录项遍历的标记位置
    long  tag = telldir(dir);

    struct dirent * dt = readdir(dir);
    while(dt != NULL){
        printf("     %s \n", dt->d_name);
        dt = readdir(dir);
    }


    // seekdir: 移动对目录流的遍历标记位置 
    seekdir(dir, tag);


    dt = readdir(dir);
    while(dt != NULL){
        printf("     %s \n", dt->d_name);
        dt = readdir(dir);
    }



    closedir(dir);

    return 0;
}

