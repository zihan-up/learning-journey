#ifndef __Thread_H__
#define __Thread_H__

#include "Noncopyable.hpp"

#include <pthread.h>
#include <functional>


namespace wd
{

using ThreadCallback=std::function<void()>;

class Thread : Noncopyable
{
public://该类对外提供的接口/功能/服务
    Thread(ThreadCallback && cb);

    void start();
    void join();

private:
    static void * start_routine(void*);


private:
    pthread_t       _pthid;
    bool            _isRunning;
    ThreadCallback  _cb;
};



}//end of namespace wd
#endif

