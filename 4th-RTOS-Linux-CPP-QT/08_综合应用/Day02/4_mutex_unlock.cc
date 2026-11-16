#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


//互斥锁在全局的位置
pthread_mutex_t mutex;


void * start_routine(void * )
{
    printf("sub thread is running.\n");

    //子线程进行加锁
    pthread_mutex_lock(&mutex);
    printf("sub thread lock success.\n");
    sleep(5);
    printf("sub thread exit\n");
    //子线程退出之前解锁了
    pthread_mutex_unlock(&mutex);
    return NULL;
}



int main()
{
    //初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    pthread_t pthid;
    pthread_create(&pthid, NULL, start_routine, NULL);
    sleep(1);
    printf("main thread is locking.\n");
    //main线程想要加锁
    pthread_mutex_lock(&mutex);
    printf("main thread lock success\n");

    //主线程要等待子线程执行结束
    pthread_join(pthid, NULL);

    //销毁互斥锁
    pthread_mutex_destroy(&mutex);
    return 0;
}

