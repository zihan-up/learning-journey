#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>

class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(QObject *parent = nullptr);
    ~MyWorker();

    //在本类中去实现自己的耗时任务
    void doTask();
    void doPlus();

signals:
    void signalQuit();



};

#endif // MYWORKER_H
