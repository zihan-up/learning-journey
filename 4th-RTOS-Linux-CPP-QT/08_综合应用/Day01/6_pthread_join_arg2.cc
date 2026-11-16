#include <stdio.h>
#include <stdlib.h>
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
    sleep(3);
    printf("after sleep...\n");

    //子线程中申请了堆空间
    int * pret = (int*)malloc(sizeof(int));
    printf("sub trhead pret: %p\n", pret);
    *pret = 10;
    //退出子线程
    return (void*)pret;//函数有返回值，执行return语句
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
    //主线程想要获取子线程退出时的返回值
    void * pretval = NULL;//void * retval = pret;
    pthread_join(pthid, &pretval);
    printf("main thread retval: %p, *pretval: %d\n", 
           pretval, *(int*)pretval);

    free(pretval);//在子线程中申请，在主线程中回收
    printf("main thread exit\n");
    return 0;
}

