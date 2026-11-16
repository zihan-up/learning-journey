#include <stdio.h>

#include <string.h>     //C语言字符串相关函数
//#include <string>     //C++标准库中的字符串std::string

#include <pthread.h>


//子线程要得到执行，必须要在main函数退出之前
//main函数退出了，整个进程就退出了，子线程无法得到执行
void * start_routine(void * arg)
{
    //cout是C++中的标准输出流对象
    //<< 输出流运算符重载，是一个函数
    //cout << "sub thread is running." << endl;
    //printf是C的标准库函数
    //在执行打印时，printf的效率高于cout
    printf("sub thread is running 2.\n");

    //while(1);//子线程死循环
    return NULL;
}


int main()
{
    pthread_t pthid, pthid2;//子线程id
    int ret = pthread_create(&pthid, NULL, start_routine, NULL);
    if(ret != 0) {
        fprintf(stderr, "%s\n", strerror(ret));
    }
    //ret = pthread_create(&pthid2, NULL, start_routine, NULL);

    printf("main thread exit\n");
    //while(1);//主线程进入死循环
    return 0;
}

