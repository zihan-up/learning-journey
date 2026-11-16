#include "ThreadPool.h"
#include "Task.h"

#include <iostream>

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
    //标志位需要更改
    _isExit = true;

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
        }
        else
        {
            cout << "nullptr == ptask" << endl;
        }
    }
}
