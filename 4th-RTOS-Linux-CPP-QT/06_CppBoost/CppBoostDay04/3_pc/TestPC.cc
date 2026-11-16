#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

int main(int argc, char *argv[])
{
    TaskQueue taskQue(10);
    Producer pro;
    Consumer con;

    thread thPro(&Producer::produce, &pro, std::ref(taskQue));//生产者子线程
    thread thCon(&Consumer::consume, &con, std::ref(taskQue));//消费者子线程

    thPro.join();
    thCon.join();

    return 0;
}

