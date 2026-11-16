#ifndef __TaskQueue_H__
#define __TaskQueue_H__

#include "MutexLock.hpp"
#include "Condition.hpp"

#include <queue>
using std::queue;
using std::size_t;

namespace wd
{

class TaskQueue
{
public:
    TaskQueue(size_t sz);

    bool empty() const;
    bool full() const;
    void push(int);
    int pop();

private:
    queue<int>  _que;
    size_t      _queSize;
    MutexLock   _mutex;
    Condition   _notEmpty;
    Condition   _notFull;

};

}// end of namespace wd


#endif

