#include "Producer.h"
#include "TaskQueue.h"
#include <chrono>
#include <system_error>
#include <thread>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

Producer::Producer()
{
}

Producer::~Producer()
{
}

//生产数据
void Producer::produce(TaskQueue &taskQue)
{
    //种随机种子
    srand(clock());
    //产生随机数
    int cnt = 20;
    while(cnt--)
    {
        int number = rand() % 100;
        taskQue.push(number);
        cout << ">>Producer produce number = " << number << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

