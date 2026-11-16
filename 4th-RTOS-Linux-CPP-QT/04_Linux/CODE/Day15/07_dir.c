#include <header.h>

int main(int argc, char *argv[argc]){

    // 打开文件流 (翻译: 打开一个文件夹, 准备去读取这个文件夹内部记录的一个个目录项, 一个子文件/子文件夹信息 )

    // 参数: 文件夹的路径
    // 返回值: 目录流的指针
    DIR * dir = opendir("./test");

    // 读取一个目录项, 读取一个之后, 目录流指针自然会下移到下一个目录项
    // 参数: 当前目录流指针的位置
    // 返回值: 结构体, 存储了读到的这个目录项的信息
    struct dirent * diren = readdir(dir);

    while(diren  != NULL){

        if(diren->d_type == DT_DIR){
            printf("目录: %s \n", diren->d_name);
        }else if(diren->d_type == DT_REG){
            printf("普通文件: %s \n", diren->d_name);
        }



        diren = readdir(dir);
    }


    closedir(dir);

    return 0;
}

