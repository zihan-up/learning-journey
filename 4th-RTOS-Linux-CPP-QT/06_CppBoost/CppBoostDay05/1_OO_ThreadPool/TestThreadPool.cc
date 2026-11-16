#include "Task.h"
#include "ThreadPool.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
: public Task
{
public:
    void process() override
    {
        //具体的实现逻辑
        srand(clock());
        int number = rand() % 100;
        cout << "MyTask number = " << number << endl;
    }
};

//正常的情况应该是：20次任务执行完毕，程序也退出来了

//线程池中存在两个问题：
//Q1：任务执行不完，程序就退出来了？
//
//Q2:任务执行完毕了，但是程序无法退出？
void test()
{
    //创建任务对象
    unique_ptr<Task> ptask(new MyTask());

    //创建线程池的对象
    ThreadPool pool(4, 10);
    //启动线程池
    pool.start();

    int cnt = 20;
    while(cnt--)
    {
        //添加任务
        pool.addTask(ptask.get());
    }

    //线程池的停止
    pool.stop();

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

