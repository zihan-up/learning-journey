#ifndef __WorkerThread_H__
#define __WorkerThread_H__

#include "Thread.hpp"
#include "Threadpool.hpp"

namespace wd
{

class WorkerThread 
: public Thread{
public:
    WorkerThread(Threadpool & tl)
    : _threadpool(tl)
    {}

private:
    void run() override
    {
        //调用的是Threadpool的私有成员函数
        _threadpool.doTask();
    }

private:
    Threadpool & _threadpool;
};

}//end of namespace wd

#endif

