#include "widget.h"

#include "myworker.h"

#include <QApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    qDebug() << "main线程的id:"
                 << QThread::currentThreadId();

    //1、创建MyWorker的对象
    MyWorker *worker = new MyWorker;

    //2、创建QThread的对象
    QThread *pth = new QThread;

    //3、将MyWorker的对象的所有权转移给QThread的对象
    worker->moveToThread(pth);

    //5、信号与槽的关键使用
    QObject::connect(pth, &QThread::started, worker, &MyWorker::doTask);
    //如果QThread中的quit函数被执行，那么QThread线程会退出事件循环
    QObject::connect(worker, &MyWorker::signalQuit, pth, &QThread::quit);

    //当QThred线程执行结束之后，会触发信号finished，可以借助这个信号连接对应的槽函数
    //回收堆空间,也可以关闭窗口
    QObject::connect(pth, &QThread::finished, worker, &MyWorker::deleteLater);
    QObject::connect(pth, &QThread::finished, pth, &QThread::deleteLater);
    QObject::connect(pth, &QThread::finished, [&a]{
        qDebug() << "线程执行结束触发了信号finished";
        a.quit();
    });

    //4、调用QThread对象的start函数启动线程
    pth->start();

    qDebug() << "QThread线程的id:"
             << pth->currentThreadId();

    return a.exec();
}
