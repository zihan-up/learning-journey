#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;

mutex mtx;//创建锁对象
mutex mtx2;//创建锁对象
int gCnt = 0;

//可以使用RAII的思想：利用栈对象的生命周期管理资源
//1、在构造函数中初始化资源
//2、在析构函数中释放资源
//3、提供若干访问资源的访问
//4、一般不允许复制或者赋值(对象语义-值语义)
class MutexLock
{
public:
    MutexLock(mutex &mutx)
    : _mtx(mutx)
    {
        _mtx.lock();
    }

    ~MutexLock()
    {
        _mtx.unlock();
    }
private:
    mutex &_mtx;
};

void threadFunc()
{
    for(int idx = 0; idx < 1000000; ++idx)
    {
        MutexLock ml(mtx);//ml就是栈对象
        ++gCnt;//拿出gCnt的值，然后执行++操作，最后取出gCnt的值
    }
}

int main(int argc, char *argv[])
{
    thread thA(threadFunc);
    thread thB(threadFunc);

    thA.join();
    thB.join();

    cout <<  "gCnt = " << gCnt << endl;

    return 0;
}

