#include <cstdio>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

//抽象基类，也就是组件类
class Component
{
public:
    //纯虚函数，提供行为接口
    virtual void operation() = 0;
    virtual ~Component(){}
};

class ConcreteComponent
: public Component
{
public:
    virtual void operation() override
    {
        cout << "具体的组件对象的方法执行" << endl;
    }
};

//定义装饰器类型
class Decorator
: public Component
{
public:
    Decorator()
    {
    }

    void setComponent(Component *pcom)
    {
        _pcom = pcom;
    }

    virtual void operation() override
    {
        if(_pcom)
        {
            _pcom->operation();//这份代码也一定会体现多态
        }
    }
private:
    Component *_pcom;
};

class ConcreteDecoratorA
: public Decorator
{
public:
    virtual void operation() override
    {
        Decorator::operation();//显示调用基类中的虚函数
        addBehavior();//调用自己的行为方法
    }

    void addBehavior()
    {
        cout << "添加A的行为或者方法" << endl;
    }
};

class ConcreteDecoratorB
: public Decorator
{
public:
    virtual void operation() override
    {
        Decorator::operation();//显示调用基类中的虚函数
        addBehavior();//调用自己的行为方法
    }

    void addBehavior()
    {
        cout << "添加B的行为或者方法" << endl;
    }
};

void test()
{
    //创建具体的组件对象
    unique_ptr<Component> pcon(new ConcreteComponent());

    //创建两个具体的装饰器对象
    unique_ptr<Decorator> pda(new ConcreteDecoratorA());
    unique_ptr<Decorator> pdb(new ConcreteDecoratorB());

    //设置三者之间的关系
    pda->setComponent(pcon.get());
    pdb->setComponent(pda.get());

    pdb->operation();//执行操作
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

