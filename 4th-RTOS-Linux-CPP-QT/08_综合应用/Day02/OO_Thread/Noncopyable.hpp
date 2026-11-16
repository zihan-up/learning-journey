#ifndef __Noncopyable_H__
#define __Noncopyable_H__

namespace wd
{

//该类不需要实例化对象, 将其设计为抽象类
class Noncopyable
{
protected:
    Noncopyable(){}
    ~Noncopyable(){}

    Noncopyable(const Noncopyable &)=delete;
    Noncopyable & operator=(const Noncopyable &)=delete;
};

}//end of namespace wd

#endif

