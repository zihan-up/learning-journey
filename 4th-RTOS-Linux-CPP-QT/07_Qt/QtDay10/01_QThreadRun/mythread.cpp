#include "mythread.h"

#include <QDebug>

MyThread::MyThread()
{

}

MyThread::~MyThread()
{

}

//run方法模拟了耗时任务
void MyThread::run()
{
    qDebug() << "子线程的id:"
             << QThread::currentThreadId();

    for(int idx = 1; idx < 10; ++idx)
    {
        qDebug() << "idx = " << idx;
        sleep(1);
    }
}
