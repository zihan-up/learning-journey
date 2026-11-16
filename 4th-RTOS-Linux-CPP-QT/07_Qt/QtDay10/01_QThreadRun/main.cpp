#include "widget.h"
#include "mythread.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    qDebug() << "main线程的id:"
             << QThread::currentThreadId();

    //1、创建子对象，该对象继承自QThread
    MyThread myTh;

    //验证线程启动的时候触发了信号started
    QObject::connect(&myTh, &MyThread::started, []{
        qDebug() << "线程启动触发了信号started";

    });

    //验证线程启动的时候触发了信号finished
//    QObject::connect(&myTh, &MyThread::finished, [&w]{
//        qDebug() << "线程执行结束触发了信号finished";
//        w.close();
//    });

    QObject::connect(&myTh, &MyThread::finished, [&a]{
        qDebug() << "线程执行结束触发了信号finished";
        a.quit();
    });

    //2、调用start函数启动线程
    myTh.start();

    return a.exec();
}
