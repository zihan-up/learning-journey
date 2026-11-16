#include "Condition.hpp"  //必须要放相应的头文件
#include "MutexLock.hpp"  //类的前向声明，需要在实现文件中添加头文件
#include <pthread.h>


//Q1. NULL和nullptr有什么区别呢？
//A1.

namespace wd
{
Condition::Condition(MutexLock & m)
: _mutex(m)
{
    pthread_cond_init(&_cond, nullptr);
}

Condition::~Condition()
{
    pthread_cond_destroy(&_cond);
}

void Condition::wait()
{
    pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
}

void Condition::notify()
{
    pthread_cond_signal(&_cond);
}

void Condition::notifyAll()
{
    pthread_cond_broadcast(&_cond);
}
}//end of namespace wd
