#include <unistd.h>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;


int main(int argc, char *argv[])
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;

    thread th([](int x){
              cout << "lambda表达式" << endl;
              cout << "child2 thread id = " << std::this_thread::get_id() << endl;
              cout << "x = " << x << endl;
              }, 6);
    cout << "child thread id = " << th.get_id() << endl;

    th.join();//让主线程等着子线程执行

    return 0;
}

