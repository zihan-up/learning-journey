#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mutex;
pthread_cond_t cond;


void * start_routine(void *)
{
    printf("sub thread %ld is running.\n", pthread_self());

    sleep(5);//子线程先休眠5秒钟

    printf("sub thread %ld is ready to signal.\n", pthread_self());
    pthread_cond_signal(&cond);
    printf("sub thread %ld has send signal.\n", pthread_self());

    sleep(2);
    printf("sub thread is locking.\n");
    //在子线程中加锁
    pthread_mutex_lock(&mutex);
    printf("\nsub thread lock success.\n");

    //解锁
    pthread_mutex_unlock(&mutex);
    return NULL;
}



int main()
{
    //初始化互斥锁
    pthread_mutex_init(&mutex, NULL);
    //初始化条件变量
    pthread_cond_init(&cond, NULL);
    //创建一个子线程
    pthread_t pthid;
    pthread_create(&pthid, NULL, start_routine, NULL);

    printf("\nmain thread before wait.\n");
    //在主线程中调用wait函数,进入阻塞状态
    pthread_cond_wait(&cond, &mutex);
    //wait函数返回之后，会打印以下语句
    printf("\nmain thread after wait\n");
    printf("main thread is joining sub thread\n");
    //主线程等待子线程执行结束
    pthread_join(pthid, NULL);
    printf("main thread: sub thread has exit.\n");

    //销毁互斥锁
    pthread_mutex_destroy(&mutex);
    //销毁条件变量
    pthread_cond_destroy(&cond);
    return 0;
}

