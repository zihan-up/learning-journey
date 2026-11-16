#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;
using std::lock_guard;

mutex mtx;//创建锁对象
int gCnt = 0;

void threadFunc()
{
    for(int idx = 0; idx < 1000000; ++idx)
    {
        //lock_guard使用了RAII的思想：利用了栈对象的生命周期管理资源
        //在构造函数中初始化资源（上锁），在析构函数中释放资源（解锁）
        //
        //lock_guard并没有提供手动解锁的方式，只能靠栈对象的生命周期结束的时候
        //进行解锁，表明该锁方式并不灵活
        
        lock_guard<mutex> lg(mtx);
        ++gCnt;//拿出gCnt的值，然后执行++操作，最后取出gCnt的值
        //xxx  不想上锁
        //yyy 上锁
        //zzz 不想上锁
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

