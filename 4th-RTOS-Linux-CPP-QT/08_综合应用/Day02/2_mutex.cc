#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    pthread_mutex_t mutex;
    //初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    //Q1. 同一个线程可以对同一把锁加锁多次吗？
    //A1. 对于互斥锁而言，同一线程不能对同一把所加锁多次
    //否则会进入阻塞状态
    pthread_mutex_lock(&mutex);
    printf("main thread lock 1st success\n");

    //加锁不成功时，线程就会阻塞
    pthread_mutex_lock(&mutex);//第二次加锁时阻塞
    printf("main thread lock 2nd success\n");

    //销毁互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}

