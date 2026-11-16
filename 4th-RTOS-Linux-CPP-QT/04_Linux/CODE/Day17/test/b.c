#include <header.h>

int main(int argc, char *argv[argc]){

    int fd = open("../1.txt", O_RDWR);

    
    char file_name[256] = {0};
    size_t name_len = 0;

    read(fd, &name_len, sizeof(size_t));
    read(fd, file_name, name_len);


    size_t str_len = 0;
    char buf[4096] = {0};

    read(fd, &str_len, sizeof(size_t));
    ssize_t ret = read(fd, buf, str_len);

    int new_fd = open(file_name, O_RDWR|O_CREAT, 0666);
    write(new_fd, buf, ret);

    close(fd);
    close(new_fd);

    return 0;
}

