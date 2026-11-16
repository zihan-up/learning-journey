#include "EventLoop.hpp"
#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include <func.h>
#include <sys/epoll.h>


namespace wd
{

EventLoop::EventLoop(Acceptor& acceptor)
: _epfd(createEpollFd())
, _acceptor(acceptor)
, _isLooping(false)
, _evtArr(1000)
{
    addEpollReadEvent(_acceptor.fd());
}

EventLoop::~EventLoop()
{
    close(_epfd);
}

void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping) {
        waitEpollFd();
    }
}

//要与loop函数运行在不同的线程
void EventLoop::unloop()
{
    _isLooping = false;
}

void EventLoop::waitEpollFd()
{
    //epoll_wait
    int nready = epoll_wait(_epfd, _evtArr.data(), _evtArr.size(), 5000);
    if(nready == -1 && errno == EINTR) {
        return;
    } else if(nready == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    } else if(nready == 0) {
        printf("epoll timeout\n");
    } else {
        //nready > 0
        for(int i = 0; i < nready; ++i) {
            int fd = _evtArr[i].data.fd;
            if(fd == _acceptor.fd()) {
                handleNewConnection();
            } else {
                handleMessage(fd);
            }
        }
    }
}


void EventLoop::handleNewConnection()
{
    //获取新连接
    int netfd = _acceptor.accept();
    //epoll添加对于netfd的监听
    addEpollReadEvent(netfd);
    //创建TcpConnection对象
    TcpConnectionPtr conn(new TcpConnection(netfd));
    //设置三个函数对象
    conn->setAllCallbacks(_onConnection,
                          _onMessage,
                          _onClose);
    //添加到容器map
    _conns.insert(std::make_pair(netfd, conn));
    //调用连接建立时的函数对象
    conn->handleNewConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
    //先通过fd查找到TcpConnection对象
    auto iter = _conns.find(fd);
    if(iter != _conns.end()) {
        //判断连接是否断开了
        bool isClosed = iter->second->isClosed();
        if(isClosed) {
            //连接断开的情况, 调用连接断开时的函数对象
            iter->second->handleCloseCallback();
            //从epoll的监听红黑树上删除
            delEpollReadEvent(fd);
            //从map中删除
            _conns.erase(fd);
        } else {
            //发送消息过来了,开始要调用消息到达时的函数对象
            iter->second->handleMessageCallback();
        }
    }
}


int EventLoop::createEpollFd()
{
    int fd = epoll_create1(0);
    if(fd < 0) {
        perror("epoll_create1");
    }
    return fd;
}
    
void EventLoop::addEpollReadEvent(int fd)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0) {
        perror("epoll_ctl");
    }
}

void EventLoop::delEpollReadEvent(int fd)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &ev);
    if(ret < 0) {
        perror("epoll_ctl");
    }
}
}//end of namespace wd
