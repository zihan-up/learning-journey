#ifndef __TASK_H__
#define __TASK_H__

class Task
{
public:
    Task();
    virtual ~Task();

    //要执行的任务
    virtual void process() = 0;

private:

};

#endif
