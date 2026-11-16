#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void threadFunc()
{
    cout << "void threadFunc()" << endl;
}

int main(int argc, char *argv[])
{
    cout << "start main..." << endl;
    thread th(threadFunc);//th就是线程对象,threadFunc称为线程入口函数
    cout << "finish main..." << endl;

    /* while(1){} */
    return 0;
}

