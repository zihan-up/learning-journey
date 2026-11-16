#include <header.h>


typedef struct stu{
  char user_name[100];
  int user_id;
}stu;

int main(int argc, char *argv[argc]){

    stu student;
    memcpy(student.user_name, "zs", 2);
    student.user_id  = 10;

    // 

    int fd = open("1.txt", O_RDWR);
    write(fd,&student , sizeof(student) );

    // 
    

    printf("%d: %s \n", student.user_id, student.user_name );

    return 0;
}

