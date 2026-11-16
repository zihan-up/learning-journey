#ifndef __TaskQueue_H__
#define __TaskQueue_H__

#include "MutexLock.hpp"
#include "Condition.hpp"
#include "Task.hpp"

#include <queue>
using std::queue;
using std::size_t;

namespace wd
{

using ElemType = Task;

class TaskQueue
{
public:
    TaskQueue(size_t sz);

    bool empty() const;
    bool full() const;
    void push(ElemType && elem);
    ElemType pop();
    void wakeup();

private:
    queue<ElemType>  _que;
    size_t      _queSize;
    MutexLock   _mutex;
    Condition   _notEmpty;
    Condition   _notFull;
    bool        _flag;

};

}// end of namespace wd


#endif

