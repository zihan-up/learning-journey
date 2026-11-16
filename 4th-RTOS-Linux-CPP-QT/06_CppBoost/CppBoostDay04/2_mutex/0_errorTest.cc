#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

int gCnt = 0;

void threadFuncA()
{
    for(int idx = 0; idx < 1000000; ++idx)
    {
        ++gCnt;
    }
}

void threadFuncB(int x)
{
    for(int idx = 0; idx < 1000000; ++idx)
    {
        ++gCnt;
    }
}

int main(int argc, char *argv[])
{
    thread thA(threadFuncA);
    thread thB(threadFuncB, 3);

    thA.join();
    thB.join();

    cout <<  "gCnt = " << gCnt << endl;

    return 0;
}

