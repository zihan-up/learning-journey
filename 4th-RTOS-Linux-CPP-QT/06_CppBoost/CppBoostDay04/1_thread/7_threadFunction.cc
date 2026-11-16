#include <iostream>
#include <thread>
#include <functional>

using std::cout;
using std::endl;
using std::thread;
using std::function;


int main(int argc, char *argv[])
{
    cout << "main thread id = " << std::this_thread::get_id() << endl;

    function<void(int)> f =  [](int x){
              cout << "lambda表达式" << endl;
              cout << "child2 thread id = " << std::this_thread::get_id() << endl;
              cout << "x = " << x << endl;
              };

    thread th(f, 7);
    cout << "child thread id = " << th.get_id() << endl;

    th.join();//让主线程等着子线程执行

    return 0;
}

