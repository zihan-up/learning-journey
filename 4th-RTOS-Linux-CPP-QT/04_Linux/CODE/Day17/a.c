#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("1.txt", O_RDWR);

    char *file_name = "file.txt";
    char *str = "hello";

    size_t name_len = strlen(file_name);
    size_t str_len = strlen(str);



    write(fd, &name_len, sizeof(size_t));
    write(fd, file_name, strlen(file_name));
    write(fd, &str_len, sizeof(size_t));
    write(fd, str, strlen(str));

    close(fd);
    return 0;
}

