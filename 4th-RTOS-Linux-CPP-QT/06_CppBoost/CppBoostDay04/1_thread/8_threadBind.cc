#include <iostream>
#include <thread>
#include <functional>

using std::cout;
using std::endl;
using std::thread;
using std::bind;

void threadFunc(int x)
{
    cout << "void threadFunc()" << endl;
    cout << "child2 thread id = " << std::this_thread::get_id() << endl;
    cout << "x = " << x << endl;
}

int main(int argc, char *argv[])
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;

    thread th(bind(threadFunc, 8));

    cout << "child thread id = " << th.get_id() << endl;

    th.join();//让主线程等着子线程执行

    return 0;
}

