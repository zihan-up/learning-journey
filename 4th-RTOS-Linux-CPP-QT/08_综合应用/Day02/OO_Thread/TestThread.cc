#include "Thread.hpp"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyThread
: public wd::Thread
{
public:
    ~MyThread() {   cout << "~MyThread()" << endl;}

    //MyThread(const MyThread&) = delete;
    //MyThread & operator=(const MyThread&)=delete;

private:
    void run() override
    {
        srand(time(NULL));
        int cnt = 10;
        while(cnt-- > 0) {
            int number = rand() % 100;
            cout << "make a number: " << number << endl;
            sleep(1);
        }
    }

};

void test0()
{
    //Q1. 线程可以进行复制吗？
    //A1. 线程是系统资源，在语义上不能进行复制的
    //应该表达对象语义(禁止复制)
    //所以拷贝构造函数和赋值运算符函数都不能直接调用
    MyThread t1;
    MyThread t2 = t1;//error
    MyThread t3;
    t3 = t1;//error
}


int main()
{
    unique_ptr<wd::Thread> thread(new MyThread);
    thread->start();//开启子线程的运行
    thread->join();//等待子线程执行结束

    return 0;
}

