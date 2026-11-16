#ifndef __Thread_H__
#define __Thread_H__

#include <pthread.h>


namespace wd
{

class Thread
{
public://该类对外提供的接口/功能/服务
    Thread();
    virtual ~Thread() {}

    void start();
    void join();
//protected:

private:
    virtual void run()=0;
    static void * start_routine(void*);

//public:

//protected:

private:
    pthread_t   _pthid;
    bool        _isRunning;
};



}//end of namespace wd
#endif

