#include "TaskQueue.h"

TaskQueue::TaskQueue(int capa)
: _capcacity(capa)
, _que()
, _mutex()
, _notFull()
, _notEmpty()
{

}

TaskQueue::~TaskQueue()
{

}

//生产数据与消费数据
void TaskQueue::push(ElemType ptask)
{
    unique_lock<mutex> ul(_mutex);
    while(full())//虚假唤醒
    {
        //小细节：wait函数会先释放锁，然后让线程睡眠(释放锁与睡眠是原子的)
        //wait函数在被唤醒之后，也要抢锁，只有抢到锁才能返回
        _notFull.wait(ul);
    }
    _que.push(ptask);
    _notEmpty.notify_one();
}

ElemType TaskQueue::pop()
{
    unique_lock<mutex> ul(_mutex);
    while(empty())
    {
        _notEmpty.wait(ul);
    }
    ElemType tmp = _que.front();
    _que.pop();

    _notFull.notify_one();

    return tmp;
}

//判空与判满
bool TaskQueue::full() const
{
    return _que.size() == _capcacity;
}

bool TaskQueue::empty() const
{
    return 0 == _que.size(); 
}
