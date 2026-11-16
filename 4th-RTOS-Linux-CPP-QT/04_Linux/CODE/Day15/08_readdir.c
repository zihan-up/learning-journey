#include <header.h>

// test: 作为起始目录, 遍历所有的底层文件和文件夹(不局限于一层遍历)

void p(int num){
    for(int i=0; i<num; i++){
        printf("----");
    }
}

// 谁调用这个函数, 要求提供一个文件夹的路径
// 这个函数只需要遍历这个文件夹
void get_file_name(char * path, int  num){

    num++;

    
    // 打开目录流
    DIR *dir = opendir(path);

    struct dirent *diren = readdir(dir);
    while(diren != NULL){
        // 遍历 path这个文件夹上, 记录的一个个目录项
        if(diren->d_type == DT_REG){
            // 普通文件
            p(num);
            printf("%s | %s \n", "", diren->d_name);
        }else if(diren->d_type == DT_DIR){
            // 是个目录
            p(num);
            printf("%s | %s \n", "", diren->d_name);

            // 递归遍历这个目录
            if(diren->d_name[0] != '.'){
                char newPath[500] = {0};
                sprintf(newPath, "%s/%s", path, diren->d_name);
                
                get_file_name(newPath, num);
            }
        }

        diren = readdir(dir);
    }

}


int main(int argc, char *argv[argc]){

    int num = 0;
    get_file_name("./test", num);

    return 0;
}

