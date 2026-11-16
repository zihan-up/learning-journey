#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>

using std::queue;
using std::mutex;
using std::unique_lock;
using std::condition_variable;

class TaskQueue
{
public:
    TaskQueue(int capa);
    ~TaskQueue();

    //生产数据与消费数据
    void push(const int &vale);
    int pop();

    //判空与判满
    bool full() const;
    bool empty() const;

private:
    size_t _capcacity;//任务队列的大小（容量）
    queue<int> _que;//存放数据的数据结构
    mutex _mutex;//锁
    condition_variable _notFull;//不为满的条件变量
    condition_variable _notEmpty;//不为空的条件变量

};

#endif
