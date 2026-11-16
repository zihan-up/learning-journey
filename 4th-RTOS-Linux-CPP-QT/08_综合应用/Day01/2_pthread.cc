#include <stdio.h>

#include <string.h>     //C语言字符串相关函数
//#include <string>     //C++标准库中的字符串std::string

#include <pthread.h>


void * start_routine(void * arg)
{
    printf("sub thread is running 2.\n");

    //while(1);//子线程死循环
    return NULL;
}


int main()
{
    pthread_t pthid = 0;//子线程id
    int ret = pthread_create(&pthid, NULL, start_routine, NULL);
    if(ret != 0) {
        fprintf(stderr, "%s\n", strerror(ret));
    }

    printf("sub thread id: %ld\n", pthid);

    printf("main thread exit\n");
    //while(1);//主线程进入死循环
    return 0;
}

