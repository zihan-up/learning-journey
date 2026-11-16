#include <iostream>
#include <string>
#include <list>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::unique_ptr;

//抽象的观察者的基类
class Observer
{
public:
    //更新状态的函数
    virtual void update(int x) = 0;
    virtual ~Observer() {}
};

class ConcerateObserverA
: public Observer
{
public:
    ConcerateObserverA(const string &name)
    : _name(name)
    {

    }

    virtual void update(int x)  override
    {
        cout << "ConcerateObserverA name = " << _name
             << "的状态 = "  << x << endl;
    }

private:
    string _name;//观察者的名字

};

class ConcerateObserverB
: public Observer
{
public:
    ConcerateObserverB(const string &name)
    : _name(name)
    {

    }

    virtual void update(int x)  override
    {
        cout << "ConcerateObserverB name = " << _name
             << "的状态 = "  << x << endl;
    }

private:
    string _name;//观察者的名字

};

//抽象的主题
class Subject
{
public:
    //添加观察者
    virtual void attach(Observer *poa) = 0;
    //删除观察者
    virtual void detach(Observer *poa) = 0;
    //发通知的函数
    virtual void notify() = 0;

    virtual ~Subject() {}
};

class ConcreteSubject
: public Subject
{
public:
    //添加观察者
    virtual void attach(Observer *poa) override
    {
        if(poa)
        {
            _obList.push_back(poa);
        }
    }

    //删除观察者
    virtual void detach(Observer *poa) override
    {
        if(poa)
        {
            _obList.remove(poa);
        }
    }

    //发通知的函数
    virtual void notify() override
    {
        for(auto &obj : _obList)
        {
            //从语法角度来来，obj是基类Observer类型的指针，该指针
            //调用纯虚函数update，所以此处一定会发生多态
            obj->update(_status);//更新状态
        }
    }

    void setStatus(int status)
    {
        _status = status;
    }

    int getStatus() const
    {
        return _status;
    }
private:
    list<Observer *> _obList;//存放所有观察者对象的容器
    int _status;//状态
};

void test()
{
    //创建两个观察者对象
    unique_ptr<Observer> poa(new ConcerateObserverA("lili"));
    unique_ptr<Observer> pob(new ConcerateObserverB("lucy"));

    //创建主题对象
    unique_ptr<ConcreteSubject> psub(new ConcreteSubject());

    //将两个观察者添加到主题中
    psub->attach(poa.get());
    psub->attach(pob.get());

    //更改主题的状态
    psub->setStatus(10);

    //可以发通知给每个观察者
    psub->notify();

    cout <<endl <<endl;
    //如果现在某个观察者不想关注主题,就应该取消关注
    psub->detach(pob.get());
    
    //如果主题在此更改状态
    psub->setStatus(20);

    //可以发通知给每个观察者
    psub->notify();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

