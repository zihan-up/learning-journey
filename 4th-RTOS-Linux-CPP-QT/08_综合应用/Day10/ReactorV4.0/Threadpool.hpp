#ifndef __Threadpool_H__
#define __Threadpool_H__

#include "Task.hpp"
#include "Thread.hpp"
#include "TaskQueue.hpp"

#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;


namespace wd
{


class Threadpool
{
public:
    Threadpool(int,int);
    ~Threadpool();

    void start();
    void stop();
    void addTask(Task && cb);
private:
    //这个是线程池要求子线程要去做的事儿
    void doTask();

private:
    vector<unique_ptr<Thread>>  _threads;
    size_t                      _threadNum;
    TaskQueue                   _taskque;
    bool                        _isExit;
};


}//end of namespace wd

#endif

