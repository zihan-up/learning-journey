#ifndef __Eventfd_H__
#define __Eventfd_H__

#include <functional>

namespace wd
{

using EventCallback=std::function<void()>;

class Eventfd
{
public:
    Eventfd(EventCallback && cb);
    ~Eventfd();

    void start();
    void wakeup();
    void stop();
private:
    int createEventFd();
    void handleReadEvent();

private:
    int             _eventfd;
    EventCallback   _cb;
    bool            _isStarted;
};


}//end of namespac wd


#endif

