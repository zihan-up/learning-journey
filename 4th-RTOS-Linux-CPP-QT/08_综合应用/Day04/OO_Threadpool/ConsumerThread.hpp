#ifndef __ConsumerThread_H__
#define __ConsumerThread_H__

#include "Thread.hpp"
#include "TaskQueue.hpp"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

class ConsumerThread
: public wd::Thread
{
public:
    ConsumerThread(wd::TaskQueue & q)
    : _que(q)
    {}

private:
    void run() override 
    {
        int cnt = 20;
        while(cnt-- > 0) {
            int number = _que.pop();
            cout << ">> consume a number:" << number << endl;
            /* sleep(1); */
        }
    }

private:
    wd::TaskQueue & _que;
};

#endif

