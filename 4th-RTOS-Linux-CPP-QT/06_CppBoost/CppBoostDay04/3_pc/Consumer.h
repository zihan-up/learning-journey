#ifndef __CONSUMER_H__
#define __CONSUMER_H__

class TaskQueue;

class Consumer
{
public:
    Consumer();
    ~Consumer();

    //消费函数
    void consume(TaskQueue &taskQue);

private:

};

#endif
