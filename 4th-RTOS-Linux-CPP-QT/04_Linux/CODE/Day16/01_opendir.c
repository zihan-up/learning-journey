#include <header.h>

int main(int argc, char *argv[argc]){

    DIR *dir = opendir("./test");
    ERROR_CHECK(dir, NULL, "opendir");




    closedir(dir);

    return 0;
}

