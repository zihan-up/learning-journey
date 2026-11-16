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
void TaskQueue::push(const int &value)
{
    //1、先获取锁
    /* _mutex.lock(); */
    unique_lock<mutex> ul(_mutex);
    //2、判断任务队列是不是满的
    while(full())//虚假唤醒
    {
        //2.1、如果任务队列是满的，需要让生产者在条件变量上睡眠
        //小细节：wait函数会先释放锁，然后让线程睡眠(释放锁与睡眠是原子的)
        //wait函数在被唤醒之后，也要抢锁，只有抢到锁才能返回
        _notFull.wait(ul);
    }
    //2.2、如果任务队列不满，需要将数据添加到任务队列中,还需要将消费者唤醒
    _que.push(value);
    _notEmpty.notify_one();
    //最后一步要进行解锁
    /* _mutex.unlock(); */
}

int TaskQueue::pop()
{
    //1、先获取锁
    unique_lock<mutex> ul(_mutex);
    //2、判断任务队列是不是空的
    while(empty())
    {
        //2.1、如果任务队列是空的，需要让消费者在条件变量上睡眠
        _notEmpty.wait(ul);
    }
    //2.2、如果任务队列不空，需要从任务队列中获取数据,需要将生产者唤醒
    int tmp = _que.front();
    _que.pop();

    _notFull.notify_one();
    //最后一步要进行解锁

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
