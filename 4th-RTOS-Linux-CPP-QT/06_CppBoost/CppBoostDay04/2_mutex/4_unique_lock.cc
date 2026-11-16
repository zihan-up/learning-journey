#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;
using std::unique_lock;

mutex mtx;//创建锁对象
int gCnt = 0;

void threadFunc()
{
    for(int idx = 0; idx < 1000000; ++idx)
    {
        //unique_lock使用了RAII的思想：利用了栈对象的生命周期管理资源
        //在构造函数中初始化资源（上锁），在析构函数中释放资源（解锁）
        //除此之外，unique_lock还提供了手动上锁lock函数以及手动解锁
        //unlock函数，就可以根据需求随时上锁与解锁，更加灵活
        
        unique_lock<mutex> ul(mtx);
        ++gCnt;//拿出gCnt的值，然后执行++操作，最后取出gCnt的值
        ul.unlock();
        //xxx  不想上锁
        ul.lock();
        //yyy 上锁
        ul.unlock();
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

