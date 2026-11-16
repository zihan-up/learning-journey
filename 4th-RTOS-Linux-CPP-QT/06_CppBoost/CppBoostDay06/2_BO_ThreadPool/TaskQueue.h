#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;
using std::function;

using ElemType = function<void()>;

class TaskQueue
{
public:
    TaskQueue(int capa);
    ~TaskQueue();

    //生产数据与消费数据
    void push(ElemType &&taskcb);
    ElemType pop();

    //判空与判满
    bool full() const;
    bool empty() const;

    //将所有在_notEmpty条件变量上的线程唤醒
    void wakeup();

private:
    size_t             _capcacity;//任务队列的大小（容量）
    queue<ElemType>    _que;//存放数据的数据结构
    mutex              _mutex;//锁
    condition_variable _notFull;//不为满的条件变量
    condition_variable _notEmpty;//不为空的条件变量
    bool               _flag;//标识工作线程被全部唤醒跳出while循环的标志位

};

#endif
