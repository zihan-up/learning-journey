#include "Eventfd.hpp"

#include <func.h>

#include <thread>


struct Mytask
{
    void process()
    {
        ::srand(time(nullptr));
        int number = ::rand() % 100;
        printf(">> make a number: %d\n", number);
    }
};

int main()
{
    wd::Eventfd eventfd(std::bind(&Mytask::process, Mytask()));
    //创建子线程，并执行eventfd对象的start函数
    std::thread t(std::bind(&wd::Eventfd::start, &eventfd));

    int cnt = 10;
    while(cnt-- > 0) {
        //主线程通知子线程执行任务
        eventfd.wakeup();
        printf("main thread cnt: %d\n", cnt);
    }

    printf("\nmain thread notify finished.\n");
    sleep(1);
    eventfd.stop();
    t.join();

    printf("\nmain thread exit.\n");
    return 0;
}

