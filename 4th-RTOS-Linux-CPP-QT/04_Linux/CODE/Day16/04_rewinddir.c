#include <header.h>

int main(int argc, char *argv[argc]){

    DIR *dir = opendir("./test");


    struct dirent * dt = readdir(dir);
    while(dt != NULL){
        printf("     %s \n", dt->d_name);
        dt = readdir(dir);
    }


    rewinddir(dir);


    dt = readdir(dir);
    while(dt != NULL){
        printf("     %s \n", dt->d_name);
        dt = readdir(dir);
    }



    closedir(dir);

    return 0;
}

