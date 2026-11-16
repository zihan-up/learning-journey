#include <unistd.h>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void threadFunc()
{
    cout << "void threadFunc()" << endl;
    cout << "child2 thread id = " << std::this_thread::get_id() << endl;
    /* sleep(3); */
    /* while(1){} */
}

int main(int argc, char *argv[])
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;
    cout << "start main..." << endl;
    thread th(threadFunc);//th就是线程对象,threadFunc称为线程入口函数
    cout << "child thread id = " << th.get_id() << endl;
    cout << "finish main..." << endl;

    /* while(1){} */
    //n + shift + k,可以跳转到函数的man手册中
    /* sleep(3); */
    th.join();//让主线程等着子线程执行

    cout << "=======" << endl;

    return 0;
}

