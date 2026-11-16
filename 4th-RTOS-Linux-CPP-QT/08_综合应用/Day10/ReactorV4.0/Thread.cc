#include "Thread.hpp"
#include <stdio.h>
#include <string.h>

namespace wd
{
//在构造函数中，形参cb是一个右值引用，
//但本身是有名字的，是一个左值
//右值引用只能绑定到右值,(右值是一个即将被销毁的对象[表达式])
//右值引用的出现是为了进行转移
Thread::Thread(ThreadCallback && cb)
: _pthid(0)
, _isRunning(false)
//, _cb(cb)//调用的是std::function的拷贝构造函数
, _cb(std::move(cb))//调用的是移动构造函数
{   //std::move的作用是显式的将一个左值转换为右值
    //&cb;//ok, 左值
}


void Thread::start()
{
    if(!_isRunning) {
        int ret = pthread_create(&_pthid, nullptr, 
                                 start_routine, this);
        if(ret != 0) {
            fprintf(stderr, "%s\n", strerror(ret));
            return;
        }
        _isRunning = true;
        return ;
    }
}

void Thread::join()
{
    if(_isRunning) {
        pthread_join(_pthid, NULL);
        _isRunning = false;
    }
}

void * Thread::start_routine(void * arg)
{
    Thread * pthread = static_cast<Thread*>(arg);
    if(pthread) {
        pthread->_cb();
    }
    return NULL;
}


}// end of namespace wd
