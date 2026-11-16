#ifndef __Condition_H__
#define __Condition_H__

#include "Noncopyable.hpp"//1. 双引号表示自定义头文件,从当前路径之下查找

//#include <stdlib.h>
//#include <string>

//#include <stdio.h>       //2. C语言的相关头文件
#include <pthread.h>       //尖括号是从系统路径之下开始查找

//#include <iostream>      //3. C++头文件

//#include <log4cpp/Category.hh>  //4. 第三方库头文件

namespace wd
{

class MutexLock;//类的前向声明, 在实现文件中加载头文件

class Condition 
: Noncopyable {
public:
    Condition(MutexLock &);
    ~Condition();

    void wait();
    void notify();
    void notifyAll();

private: 
    pthread_cond_t _cond;
    MutexLock & _mutex;//引用依然占据一个指针大小的空间
};

}//end of namespace wd


#endif

