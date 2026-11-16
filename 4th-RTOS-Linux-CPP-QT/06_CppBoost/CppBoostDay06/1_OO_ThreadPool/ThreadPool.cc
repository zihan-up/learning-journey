#include "ThreadPool.h"
#include "Task.h"

#include <chrono>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t capa)
: _threadNum(threadNum)
, _threads()
, _capacity(capa)
, _taskQue(_capacity)
, _isExit(false)
{
}

ThreadPool::~ThreadPool()
{

}

//线程池的启动与停止
void ThreadPool::start()
{
    for(size_t idx = 0; idx < _threadNum; ++idx)
    {
        //1、工作线程如何创建
        //2、创建出来之后要做什么，还需要存放在vector
        /* thread th(&ThreadPool::doTask, this); */
        /* _threads.push_back(std::move(th)); */
        _threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

void ThreadPool::stop()
{
    //只要任务队列不为空，就不能让主线程继续向下执行，将标志为_isExit设置为true
    while(!_taskQue.empty())
    {
        //卡在这里,为了让主线程在此时让出CPU的控制权，也就是提升CPU执行效率，可以
        //在此处让主线程睡眠，主动让出CPU的控制权
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    //标志位需要更改
    _isExit = true;

    //如果走到这里来了之后，子线程处于睡眠状态，那么主线程再将所有的子线程唤醒
    /* _notEmpty.notify_all(); */
    //将所有在_notEmpty条件变量上的线程唤醒
    _taskQue.wakeup();

    //让主线程等着子线程的执行完毕
    for(auto &th : _threads)
    {
        th.join();
    }
}

//添加任务与获取任务
void ThreadPool::addTask(Task *ptask)
{
    if(ptask)
    {
        _taskQue.push(ptask);
    }
}

Task *ThreadPool::getTask()
{
    return _taskQue.pop();
}

//线程池中的工作线程的入口函数
void ThreadPool::doTask()
{
    //1、只要任务队列不为空，就可以让子线程一直拿任务并执行任务
    //但是解决不了任务是分批添加的
    /* while(!_taskQue.empty()) */
    //2、只要线程池不退出，那么即使任务执行完毕了，也不能让线程池
    //中的线程退出（可以等着任务的到来）
    while(!_isExit)
    {
        //线程池中的线程要拿任务，然后执行任务
        Task *ptask = getTask();
        if(ptask)
        {
            ptask->process();//体现多态
            /* std::this_thread::sleep_for(std::chrono::seconds(3)); */
        }
        else
        {
            cout << "nullptr == ptask" << endl;
        }
    }
}
