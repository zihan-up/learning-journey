#include "Thread.hpp"

#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class Mytask
{
public:
    ~Mytask() {   cout << "~MyThread()" << endl;}

    void process() 
    {
        cout << "Bo_Thread Test" << endl;
        srand(time(NULL));
        int cnt = 10;
        while(cnt-- > 0) {
            int number = rand() % 100;
            cout << "make a number: " << number << endl;
            sleep(1);
        }
    }
};


int main()
{
    unique_ptr<wd::Thread> thread(new wd::Thread(
            std::bind(&Mytask::process, Mytask())));
    thread->start();//开启子线程的运行
    thread->join();//等待子线程执行结束

    return 0;
}

