#include "TaskQueue.hpp"
#include "ProducerThread.hpp"
#include "ConsumerThread.hpp"

#include <memory>

using std::unique_ptr;

int main()
{
    wd::TaskQueue taskque(10);
    unique_ptr<wd::Thread> producer(new ProducerThread(taskque));
    unique_ptr<wd::Thread> consumer(new ConsumerThread(taskque));
    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    return 0;
}

