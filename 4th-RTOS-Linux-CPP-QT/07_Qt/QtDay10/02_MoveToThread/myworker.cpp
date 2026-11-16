#include "myworker.h"

#include <QDebug>
#include <QThread>

MyWorker::MyWorker(QObject *parent) : QObject(parent)
{

}

MyWorker::~MyWorker()
{

}

//在本类中去实现自己的耗时任务
void MyWorker::doTask()
{
    qDebug() << "子线程的id:"
                << QThread::currentThreadId();

    for(int idx = 1; idx < 10; ++idx)
    {
        qDebug() << "idx = " << idx;
        QThread::sleep(1);
    }

    //耗时任务执行结束后，触发信号signalQuit
    emit signalQuit();
}
