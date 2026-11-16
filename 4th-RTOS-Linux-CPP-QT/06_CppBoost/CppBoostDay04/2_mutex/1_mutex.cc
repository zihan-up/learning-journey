#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;

mutex mtx;//创建锁对象
int gCnt = 0;

void threadFunc()
{
    for(int idx = 0; idx < 1000000; ++idx)
    {
        //std::mutex如果只上锁没有解锁，会导致程序一直处于锁定状态
        //但是有时确实忘记了解锁，这个时候，这种锁是存在缺陷的
        //或者说有不安全的风险的
        mtx.lock();
        ++gCnt;//拿出gCnt的值，然后执行++操作，最后取出gCnt的值
        mtx.unlock();
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

