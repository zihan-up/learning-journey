#ifndef __Noncopyable_H__
#define __Noncopyable_H__

namespace wd
{

//因为不需要单独创建一个Noncopyable的对象，
//所以将其设置为抽象类
class Noncopyable
{
protected:
    Noncopyable(){}
    ~Noncopyable() {}

    Noncopyable(const Noncopyable & rhs)= delete;
    Noncopyable & operator=(const Noncopyable &) = delete;
};

}//end of namespace wd


#endif

