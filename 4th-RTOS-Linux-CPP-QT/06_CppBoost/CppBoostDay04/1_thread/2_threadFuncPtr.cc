#include <unistd.h>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void threadFunc(int x)
{
    cout << "void threadFunc()" << endl;
    cout << "child2 thread id = " << std::this_thread::get_id() << endl;
    cout << "x = " << x << endl;
}

int main(int argc, char *argv[])
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;

    void (*pFunc)(int) = threadFunc;

    thread th(pFunc, 2);//th就是线程对象,threadFunc称为线程入口函数
    cout << "child thread id = " << th.get_id() << endl;

    th.join();//让主线程等着子线程执行

    cout << "=======" << endl;

    return 0;
}

