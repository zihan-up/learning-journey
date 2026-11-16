#ifndef MYTREAD_H
#define MYTREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    ~MyThread();

    //重写run
    void run() override;
};

#endif // MYTREAD_H
