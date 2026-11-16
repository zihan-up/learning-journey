#include "ThreadPool.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;

class MyTask
{
public:
    void process(int x) 
    {
        //具体的实现逻辑
        srand(clock());
        int number = rand() % 100;
        cout << ">>BO_ThreadPool.MyTask number = " << number << endl;
    }
};

//正常的情况应该是：20次任务执行完毕，程序也退出来了

//线程池中存在两个问题：
//Q1：任务执行不完，程序就退出来了？
//A1:如果主线程在添加完20次任务之后，会执行stop函数，将标志位_isExit设置为true
//同时执行join函数，等待子线程，如果子线程执行完上一次任务之后，在继续执行while
//的时候，发现标志位已经被修改为了true，那么while就无法进行，就会提前结束子线程
//的执行，也就是任务执行不完毕
//
//解决方案：只要任务队列不为空，那么即使主线程执行的比较快，进入到了stop函数中
//也不能继续向下执行，将标志为_isExit设置成true,在stop中添加代码，只要任务
//队列不为空，那么主线程就睡眠，while(!_taskQue.empty){//睡眠}
//
//
//Q2:任务执行完毕了，但是程序无法退出？
//A2:子线程创建之后，会走线程入口函数，也就是doTask；而主线程在添加完20次任务之后
//会执行stop函数，但是只要任务执行不完，主线程会等着线程（主线程在stop函数中睡眠）
//第一种情况：假如子线程将最后几个任务获取完毕之后，也就是在doTask中执行了getTask
//那么此时任务队列就为空，如果子线程执行的比较快，可以将process函数执行完毕之后，
//会继续走while循环，但是此时标志位依旧为false，那么子线程会继续进入到while循环中
//执行getTask，但是因为没有任务可以获取，所以子线程也就会睡眠,那么主线程会继续
//等着子线程，也就程序无法退出（子线程执行的快）
//
//第二种情况，假如子线程将最后几个任务执行完毕之后，也就是在doTask中执行了getTask
//，那么此时任务队列为空，如果正好主线程执行的比较快，将标志位_isExit设置为true
//并且执行后面的join，那么主线程会等待着子线程，而子线程在执行完getTask，然后执行
//process之后，在走while循环的时候，发现标志位_isExit已经为true，那么while循环就
//无法进入，那么主线程就会回收子线程（主线程执行的比较快，就没有问题）
//
//解决方案：第二种情况就是主线程执行要快，那么程序是没有问题的，所以不需要添加
//额外的代码，但是第一种情况的时候，如果子线程执行的比较快，也就是会在执行
//任务之后，继续执行getTask，但是因为没有任务可以被获取，导致所有的工作线程在
//_notEmpty条件变量上睡觉，所以解决方案是，让主线程在回收子线程的时候，将所有
//可能睡觉的线程全部唤醒并且回收
void test()
{
    //创建任务对象
    unique_ptr<MyTask> ptask(new MyTask());

    //创建线程池的对象
    ThreadPool pool(4, 10);
    //启动线程池
    pool.start();

    int cnt = 20;
    while(cnt--)
    {
        //添加任务
        pool.addTask(bind(&MyTask::process, ptask.get(), 100));
        cout << "cnt = " << cnt << endl;
    }

    //线程池的停止
    pool.stop();

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

