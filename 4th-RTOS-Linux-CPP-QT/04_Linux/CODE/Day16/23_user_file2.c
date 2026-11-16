#include <header.h>


typedef struct stu{
  char user_name[100];
  int user_id;
}stu;

int main(int argc, char *argv[argc]){

    stu student;

    int fd = open("1.txt", O_RDWR);
    read(fd,&student , sizeof(student) );

    // 
    

    printf("%d: %s \n", student.user_id, student.user_name );

    return 0;
}

