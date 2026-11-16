#include "TaskQueue.h"

TaskQueue::TaskQueue(int capa)
: _capcacity(capa)
, _que()
, _mutex()
, _notFull()
, _notEmpty()
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//生产数据与消费数据
void TaskQueue::push(ElemType &&taskcb)
{
    unique_lock<mutex> ul(_mutex);
    while(full())//虚假唤醒
    {
        //小细节：wait函数会先释放锁，然后让线程睡眠(释放锁与睡眠是原子的)
        //wait函数在被唤醒之后，也要抢锁，只有抢到锁才能返回
        _notFull.wait(ul);
    }
    _que.push(std::move(taskcb));
    _notEmpty.notify_one();
}

ElemType TaskQueue::pop()
{
    unique_lock<mutex> ul(_mutex);
    while(empty() && _flag)//加上了标志位_flag
    {
        _notEmpty.wait(ul);
    }

    if(_flag)
    {
        ElemType tmp = _que.front();
        _que.pop();

        _notFull.notify_one();

        return tmp;
    }
    else
    {
        return nullptr;
    }
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

//将所有在_notEmpty条件变量上的线程唤醒
void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notify_all();
}
