#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>     //C语言字符串相关函数
//#include <string>     //C++标准库中的字符串std::string


//子线程入口函数
void * start_routine(void * arg)
{
    printf("\nsub thread is running 2.\n");
    //在子线程内部如何获取子线程的id？
    printf("sub thread id: %ld\n", pthread_self());
    sleep(8);
    printf("after sleep...\n");

    //退出子线程
    //pthread_exit(NULL);
    return NULL;//函数有返回值，执行return语句
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

    //而应该是主线程要等待子线程执行结束
    //当线程pthid未退出时，主线程就会进入阻塞状态;
    //一旦子线程执行结束，pthread_join函数就会返回
    pthread_join(pthid, NULL);
    printf("main thread exit\n");
    return 0;
}

