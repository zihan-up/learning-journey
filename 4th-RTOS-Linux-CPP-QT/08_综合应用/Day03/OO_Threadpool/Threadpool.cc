#include "Threadpool.hpp"
#include "WorkerThread.hpp"

#include <unistd.h>

namespace wd
{

Threadpool::Threadpool(int threadNum, int queSize)
: _threads()
, _threadNum(threadNum)
, _taskque(queSize)
, _isExit(false)
{
    //只开空间，没有元素
    _threads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
    if(!_isExit) {
        stop();
    }
}

//开启N个子线程的执行
void Threadpool::start()
{
    for(int i = 0; i < _threadNum; ++i) {
        unique_ptr<Thread> up(new WorkerThread(*this));
        _threads.push_back(std::move(up));
    }

    for(auto & pthread : _threads) {
        pthread->start();
    }
}
    
void Threadpool::addTask(Task * ptask)
{
    if(ptask) {
        _taskque.push(ptask);
    }
}

void Threadpool::stop()
{
    //停止线程池的运行
    while(!_taskque.empty()) {
        //当还有任务咩有执行完毕，就继续执行
        sleep(1);
    }

    //修改线程池退出时的状态标志位
    _isExit = true;

    //回收每一个子线程
    for(auto & pthread : _threads) {
        pthread->join();
    }
}


void Threadpool::doTask()
{
    //不断的从任务队列中获取任务，并执行
    while(!_isExit) {
        Task * ptask = _taskque.pop();
        if(ptask) {
            ptask->process();//执行任务
        }
    }
}
}//end of namespace wd
