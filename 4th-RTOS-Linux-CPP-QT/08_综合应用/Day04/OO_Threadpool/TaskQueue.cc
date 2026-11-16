
#include "TaskQueue.hpp"
#include "MutexLock.hpp"

namespace wd
{


TaskQueue::TaskQueue(size_t sz)
: _que() 
, _queSize(sz)
, _mutex()
, _notEmpty(_mutex) //必须要加上
, _notFull(_mutex)
, _flag(true)
{}

bool TaskQueue::empty() const
{
    return _que.size() == 0;
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

//运行在生产者的线程
void TaskQueue::push(ElemType elem)
{
    //先加锁
    MutexLockGuard autolock(_mutex);
    //再判断条件
    while(full()) {
        //当队列已满时，只能等待，不能放数据
        _notFull.wait();
    }

    _que.push(elem);//将元素放入队列
    //通知消费者线程取数据
    _notEmpty.notify();
}

//运行在消费者的线程
ElemType TaskQueue::pop()
{
    //RAII(Resource Acquisition Is Initialization)
    //局部对象，当函数执行结束时，一定会解锁
    MutexLockGuard autolock(_mutex);
    //判断条件是否满足
    while(_flag && empty()) {
        _notEmpty.wait();
    }

    if(_flag) {
        //获取队列头部的元素
        ElemType tmp = _que.front();
        //从队列中删除掉
        _que.pop();

        //通知生产者线程放数据
        _notFull.notify();
        return tmp;
    } else {
        return nullptr;
    }
}

void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notifyAll();
}

}//end of namespace wd
