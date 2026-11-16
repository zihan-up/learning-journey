#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;


int gnumber = 0;
pthread_mutex_t mutex;


void * start_routine1(void *)
{
    printf("sub thread 1 is running.\n");
    int cnt = 100000;
    while(cnt-- > 0) {
        //减小加锁的范围
        pthread_mutex_lock(&mutex);
        ++gnumber;
        printf("sub thread 1 gnumber: %d\n", gnumber);
        pthread_mutex_unlock(&mutex);
    }
    printf("sub thread 1 gnumber: %d\n", gnumber);
    return NULL;
}

void * start_routine2(void *)
{
    printf("sub thread 2 is running.\n");
    int cnt = 100000;
    while(cnt-- > 0) {
        //减小加锁的范围
        pthread_mutex_lock(&mutex);
        ++gnumber;
        printf("sub thread 2 gnumber: %d\n", gnumber);
        pthread_mutex_unlock(&mutex);
    }
    printf("sub thread 2 gnumber: %d\n", gnumber);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t pthid1, pthid2;
    pthread_create(&pthid1, NULL, start_routine1, NULL);
    pthread_create(&pthid2, NULL, start_routine2, NULL);

    pthread_join(pthid1, NULL);
    pthread_join(pthid2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("main thread gnumber: %d\n", gnumber);
    return 0;
}

