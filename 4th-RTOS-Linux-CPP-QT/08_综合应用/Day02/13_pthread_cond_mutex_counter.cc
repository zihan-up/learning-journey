#include <stdio.h>
#include <pthread.h>


bool flag = true;
int gnumber = 0;//临界资源(互斥访问)
pthread_mutex_t mutex;
pthread_cond_t cond;


void * start_routine1(void *)
{
    printf("sub thread 1 is running.\n");
    int cnt = 100000;
    while(cnt-- > 0) {
        //减小加锁的范围
        pthread_mutex_lock(&mutex);
        //将if换成while是为了防止出现虚假唤醒
        while(flag == true) {
            pthread_cond_wait(&cond, &mutex);
        }
        //flag为false时，进行修改
        ++gnumber;
        printf("sub thread 1 gnumber: %d\n", gnumber);
        flag = true;
        //通知2号线程修改数据
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    //printf("sub thread 1 gnumber: %d\n", gnumber);
    return NULL;
}

void * start_routine2(void *)
{
    printf("sub thread 2 is running.\n");
    int cnt = 100000;
    while(cnt-- > 0) {
        //减小加锁的范围
        pthread_mutex_lock(&mutex);
        while(flag == false) {
            //当flag为false时，进入等待状态
            pthread_cond_wait(&cond, &mutex);
        }
        //flag为true时，进行修改
        ++gnumber;
        printf("sub thread 2 gnumber: %d\n", gnumber);
        flag = false;
        //通知1号线程修改数据
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    //printf("sub thread 2 gnumber: %d\n", gnumber);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t pthid1, pthid2;
    pthread_create(&pthid1, NULL, start_routine1, NULL);
    pthread_create(&pthid2, NULL, start_routine2, NULL);

    pthread_join(pthid1, NULL);
    pthread_join(pthid2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    printf("main thread gnumber: %d\n", gnumber);
    return 0;
}

