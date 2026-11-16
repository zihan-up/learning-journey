#include "Threadpool.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <memory>

using std::unique_ptr;

class MyTask
: public wd::Task
{
public:
    void process() override
    {
        //产生一个100以内随机整数
        srand(time(nullptr));
        int number = rand() % 100;
        printf("make a number: %d\n", number);
        sleep(1);
    }
};

int main()
{
    wd::Threadpool threadpool(4, 10);
    //开始线程池的运行
    threadpool.start();

    unique_ptr<wd::Task> ptask(new MyTask);

    //在主线程中添加任务
    int cnt = 20;
    while(cnt-- > 0) {
        threadpool.addTask(ptask.get());
    }

    //停止线程池的运行
    threadpool.stop();


    return 0;
}

