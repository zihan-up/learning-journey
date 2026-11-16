#ifndef __ProducerThread_H__
#define __ProducerThread_H__

#include "TaskQueue.hpp"
#include "Thread.hpp"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;


class ProducerThread
: public wd::Thread
{
public:
    ProducerThread(wd::TaskQueue & q)
    : _que(q)
    {}

private:
    void run() override 
    {
        srand(time(nullptr));
        int cnt = 20;
        while(cnt-- > 0) {
            int number = rand() % 100;
            _que.push(number);
            cout << "make a number:" << number << endl;
            sleep(1);
        }
    }

private:
    wd::TaskQueue & _que;
};


#endif

