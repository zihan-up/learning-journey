#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class Strategy
{
public:
    //策略的抽象方法
    virtual void execute() = 0;
    virtual ~Strategy() {}
};

//具体的策略A
class ConcreteStrategyA
: public Strategy
{
public:
    virtual void execute() override
    {
        cout << "执行策略A" << endl;
    }
};

//具体的策略B
class ConcreteStrategyB
: public Strategy
{
public:
    virtual void execute() override
    {
        cout << "执行策略B" << endl;
    }
};

class Context
{
public:
    Context()
    {
    }

    //设置策略的函数（也就是更改策略的函数）
    void setStrategy(Strategy *pstra)
    {
        _pstra = pstra;
    }

    //执行策略的方式
    void executeStrategy()
    {
        if(_pstra)
        {
            _pstra->execute();//肯定此处会调用多态
        }
    }
private:
    Strategy *_pstra;
};

void test()
{
    //创建两个策略者对象
    unique_ptr<Strategy> psa(new ConcreteStrategyA());
    unique_ptr<Strategy> psb(new ConcreteStrategyB());

    unique_ptr<Context> pctx(new Context());

    //将策略设置为A
    pctx->setStrategy(psa.get());
    pctx->executeStrategy();

    cout << endl <<endl;
    pctx->setStrategy(psb.get());
    pctx->executeStrategy();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

