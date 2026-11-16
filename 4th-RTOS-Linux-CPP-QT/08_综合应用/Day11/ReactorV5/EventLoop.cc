#include "EventLoop.hpp"
#include "Acceptor.hpp"
#include "MutexLock.hpp"
#include "TcpConnection.hpp"
#include <func.h>
#include <pthread.h>
#include <sys/eventfd.h>

namespace wd
{

EventLoop::EventLoop(Acceptor & ac)
: _epfd(createEpollFd())
, _eventfd(createEventFd())
, _acceptor(ac)
, _isLooping(false)
, _evtArr(1024)
{
    //监听建立连接的服务器的文件描述符
    addEpollReadEvent(_acceptor.fd()) ;      
    //监听_eventfd的读事件
    addEpollReadEvent(_eventfd);
}
    
EventLoop::~EventLoop()
{
    if(_epfd > 0)
        close(_epfd);
}

//执行事件循环
void EventLoop::loop()
{ 
    _isLooping = true;
    while(_isLooping) {
        waitEpollFd();
    }
}
    

//交给TcpConnection对象调用的，
//用来通知IO线程发送消息的
void EventLoop::runInLoop(Functor && f)
{
    {
    //语句块可以减小加锁的范围
    MutexLockGuard autolock(_mutex);
    //共享资源，需要进行加锁
    _pendingFunctors.push_back(std::move(f));
    }

    wakeup();//唤醒epoll,通知IO线程
}

//循环执行体
//注意：每一个封装的函数尽量不要超过50行;
//如果超过50行，一定要再次进行封装，提取出新的函数
void EventLoop::waitEpollFd()
{
    //调用epoll_wait
    int nready = epoll_wait(_epfd, _evtArr.data(), _evtArr.size(), 5000);
    if(nready == -1 && errno == EINTR) {
        return;
    } else if(nready == -1) {
        perror("epoll-wait");
        return;
    } else if(nready == 0) {
        printf("epoll timeout.\n");
        return;
    } else {
        //nready > 0
        for(int i = 0; i < nready; ++i) {
            int fd = _evtArr[i].data.fd;
            if(fd == _acceptor.fd()) {
                //处理新连接
                handleNewConnection();
            } else if(fd == _eventfd) {  
                //计算线程通知IO线程
                handleReadEvent();
                doPendingFunctors();
            } else {
                //处理已经建立好的连接
                handleMessage(fd);
            }
        }
    }
}

//创建epoll的实例
int EventLoop::createEpollFd()
{
    int fd = epoll_create1(0);
    if(fd < 0) {
        perror("epoll_create1");
    }
    return fd;
}


//对某一个fd添加读事件的监听
void EventLoop::addEpollReadEvent(int fd)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));//初始化，清空操作
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev);
    if(ret < 0) {
        perror("epoll_ctl");
    }
}

void EventLoop::delEpollReadEvent(int fd)
{
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));//初始化，清空操作
    //ev.events = EPOLLIN;
    ev.data.fd = fd;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &ev);
    if(ret < 0) {
        perror("epoll_ctl");
    }
}

void EventLoop::handleNewConnection()
{
    //1. 获取与对端进行交互的netfd
    int netfd = _acceptor.accept();
    if(netfd < 0) {
        return ;
    }
    addEpollReadEvent(netfd);//添加到epoll的监听红黑树上
    //2.1 创建TcpConnection
    TcpConnectionPtr conn(new TcpConnection(netfd, this));
    //2.2 注册函数对象时，不能使用移动语义
    conn->setAllCallbacks(_onConnection,
                          _onMessage, 
                          _onClose);
    //3. 调用新连接建立时的函数对象
    conn->handleNewConnectionCallback();
    //4. 管理conn对象, 放入map中存储起来
    _conns[netfd] = conn;
}

void EventLoop::handleMessage(int fd)
{
    //1. 通过fd查找到TcpConnection对象
    auto iter = _conns.find(fd);
    if(iter != _conns.end()) {
        //2. 查找成功后，先判断连接是否断开
        bool isClosed = iter->second->isClosed();
        if(isClosed) {
            //2.1 连接断开的情况
            iter->second->handleCloseCallback();
            delEpollReadEvent(fd);//从epoll监听的红黑树上删除
            _conns.erase(fd);//从map中删除该连接对象
        } else {
            //2.2 收到消息时的情况
            iter->second->handleMessageCallback();
        }
    }
}

int EventLoop::createEventFd()
{
    int fd = ::eventfd(0, 0);
    if(fd < 0) {
        perror("eventfd");
    }
    return fd;
}

void EventLoop::handleReadEvent()
{
    uint64_t howmany = 0;
    int ret = read(_eventfd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany)) {
        perror("read");
    }
}

void EventLoop::wakeup()
{
    printf("compute thread %ld: wakeup io thread.\n",
           pthread_self());
    uint64_t one = 1;
    int ret = write(_eventfd, &one, sizeof(one));
    if(ret != sizeof(one)) {
        perror("write");
    }
}

void EventLoop::doPendingFunctors()
{
    printf("\nio thread %ld: doPendingFunctors().\n",
           pthread_self());

    vector<Functor> tmp;
    {
    MutexLockGuard autolock(_mutex);
    //交换的时间复杂度为O(1)
    tmp.swap(_pendingFunctors);
    }

    //经过交换之后，tmp中拥有了所有的回调函数
    //遍历tmp，进行回调函数的执行
    //执行发送的时候，不会影响_pendingFunctors在计算线程中的使用
    for(auto & f : tmp) {
        f();
    }
}

}//end of namespace wd
