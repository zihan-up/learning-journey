#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


pthread_mutex_t mutex;
pthread_cond_t cond;


void * start_routine1(void *)
{
    printf("sub thread 1 is running.\n");
    printf("sub thread 1 is ready to wait.\n");
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    printf("sub thread 1 has wakeup.\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void * start_routine2(void *)
{
    printf("sub thread 2 is running.\n");
    printf("sub thread 2 is ready to wait.\n");
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    printf("sub thread 2 has wakeup.\n");
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
    pthread_t pthid, pthid2;
    pthread_create(&pthid, NULL, start_routine1, NULL);
    pthread_create(&pthid2, NULL, start_routine2, NULL);

    //主线程休眠5秒钟
    sleep(5);
    //发送广播通知
    printf("main thread is ready to broacast.\n");
    pthread_cond_broadcast(&cond);

    pthread_join(pthid, NULL);
    pthread_join(pthid2, NULL);
    printf("main thread has joined sub threads.\n");

    //销毁互斥锁
    pthread_mutex_destroy(&mutex);
    //销毁条件变量
    pthread_cond_destroy(&cond);
    return 0;
}

