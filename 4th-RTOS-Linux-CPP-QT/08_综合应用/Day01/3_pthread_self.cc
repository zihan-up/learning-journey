#include <stdio.h>

#include <string.h>     //C语言字符串相关函数
//#include <string>     //C++标准库中的字符串std::string

#include <pthread.h>


//子线程入口函数
void * start_routine(void * arg)
{
    printf("\nsub thread is running 2.\n");
    //在子线程内部如何获取子线程的id？
    printf("sub thread id: %ld\n", pthread_self());

    //while(1);//子线程死循环
    return NULL;
}


//main线程有自己的函数栈空间
int main()
{
    //pthid是主线程的局部变量
    pthread_t pthid = 0;//子线程id
    int ret = pthread_create(&pthid, NULL, start_routine, NULL);
    if(ret != 0) {
        fprintf(stderr, "%s\n", strerror(ret));
    }

    printf("main sub thread id: %ld\n", pthid);
    printf("main thread id: %ld\n", pthread_self());

    printf("main thread exit\n");
    //真正写代码时，不能采用死循环的写法；
    //而应该是主线程要等待子线程执行结束
    while(1);//主线程进入死循环
    return 0;
}

