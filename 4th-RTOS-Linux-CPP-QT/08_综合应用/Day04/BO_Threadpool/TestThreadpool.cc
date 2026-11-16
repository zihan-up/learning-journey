#include "Threadpool.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <memory>

using std::unique_ptr;

class MyTask
{
public:
    void process() 
    {
        //产生一个100以内随机整数
        srand(time(nullptr));
        int number = rand() % 100;
        printf("BO Threadpool, make a number: %d\n", number);
        sleep(1);
    }
};

//函数类型由返回值和参数列表共同确定
void print()
{   printf("print()\n") ;  }


void process()
{
    //产生一个100以内随机整数
    srand(time(nullptr));
    int number = rand() % 100;
    printf("BO Threadpool2, make a number: %d\n", number);
    sleep(1);
}

int main()
{
    wd::Threadpool threadpool(4, 10);
    //开始线程池的运行
    threadpool.start();

    unique_ptr<MyTask> task(new MyTask);

    //对于普通函数而言，函数名就是一个地址值
    //那就可以将其看成是一个常量, 不是左值
    printf("&process: %p\n", &process);
    printf("process: %p\n", process);
    //process = 0x100;//error

    int && ref = 10;//ok
                    
    //在主线程中添加任务
    int cnt = 20;
    while(cnt-- > 0) {
        //std::bind提前绑定参数时，会采用值传递, 对MyTask对象进行复制
        //threadpool.addTask(std::bind(&MyTask::process, MyTask()));
        threadpool.addTask(process);
        //这种写法传递的就是MyTask对象的指针, 此时要求当process函数
        //被调用时，MyTask堆对象的生命周期必须是OK的；如果堆对象
        //已经被销毁了，才开始去执行process函数，可能会出现段错误
        //threadpool.addTask(std::bind(&MyTask::process, task.get()));
    }

    //停止线程池的运行
    threadpool.stop();


    return 0;
}

