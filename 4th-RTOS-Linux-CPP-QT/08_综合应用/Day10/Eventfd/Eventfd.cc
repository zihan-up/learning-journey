#include "Eventfd.hpp"
#include <func.h>
#include <sys/eventfd.h>
#include <poll.h>

namespace wd
{

Eventfd::Eventfd(EventCallback && cb)
: _eventfd(createEventFd())
, _cb(std::move(cb))
, _isStarted(false)
{}
    
Eventfd::~Eventfd()
{
    close(_eventfd);
}


//运行在子线程中，对_eventfd进行监听
void Eventfd::start()
{
    struct pollfd pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.fd = _eventfd;
    pfd.events = POLLIN;

    _isStarted = true;
    while(_isStarted) {
        int nready = ::poll(&pfd, 1, 5000);
        if(nready == -1 && errno == EINTR) {
            continue;
        } else if(nready == -1) {
            perror("poll");
            return;
        } else if(nready == 0) {
            printf("poll timeout.\n");
        } else {
            //触发了eventfd的读事件
            handleReadEvent();
            if(_cb) {
                _cb();
            }
        }
    }
}

void Eventfd::wakeup()
{
    uint64_t one = 1;
    int ret = write(_eventfd, &one, sizeof(one));
    if(ret != sizeof(one)) {
        perror("write");
    }
}

void Eventfd::stop()
{
    _isStarted = false;
}


int Eventfd::createEventFd()
{
    int fd = ::eventfd(0, 0);
    if(fd < 0) {
        perror("eventfd");
    }
    return fd;
}

void Eventfd::handleReadEvent()
{
    uint64_t howmany = 0;
    int ret = read(_eventfd, &howmany, sizeof(howmany));
    printf(">> howmany: %ld\n", howmany);
    if(ret != sizeof(howmany)) {
        perror("read");
    }
}

}//end of namespace wd

