#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>     //C语言字符串相关函数
//#include <string>     //C++标准库中的字符串std::string

//全局变量不需要通过线程创建函数的第四个参数进行传递
int gnumber = 1000;

//子线程入口函数
void * start_routine(void * arg)
{
    printf("\nsub thread is running.\n");
    printf("sub thread gnumber: %d, %p\n", gnumber, &gnumber);

    int * pint = (int*)arg;
    printf("sub thread *pint: %d, pint:%p\n",*pint, pint);
    //这也体现出了多线程环境下，内存地址空间是共享的
    *pint = 100;//子线程修改主线程中堆空间的变量
    //退出子线程
    return NULL;//函数有返回值，执行return语句
}


//main线程有自己的函数栈空间
int main()
{   //pnumber位于main函数栈空间
    //它指向的是一个堆空间
    int * pnumber = new int(22);
    printf("main thread number: %d, pnumber: %p\n", 
           *pnumber, pnumber);
    printf("main thread gnumber: %d, %p\n", gnumber, &gnumber);
    pthread_t pthid = 0;//子线程id
    int ret = pthread_create(&pthid, 
                             NULL, 
                             start_routine, 
                             pnumber);
    if(ret != 0) {
        fprintf(stderr, "%s\n", strerror(ret));
    }

    //而应该是主线程要等待子线程执行结束
    //主线程想要获取子线程退出时的返回值
    pthread_join(pthid, NULL);
    printf("\nmain thread number: %d, &number: %p\n", 
           *pnumber, pnumber);
    delete pnumber;//回收堆空间的数据
    printf("main thread exit\n");
    return 0;
}

