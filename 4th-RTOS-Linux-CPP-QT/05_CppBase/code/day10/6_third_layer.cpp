#include <iostream>
using std::cout;
using std::endl;
//三层结构
class Data{
public:
    Data(){
        cout << "Data()" << endl;
    }
    ~Data(){
        cout << "~Data()" << endl;
    }

    int getData(){
        return _data;
    }

private:
    int _data = 10;
};

class MiddleLayer{
public:
    //此时指针变量使用的是何种方式进行初始化?
    //浅拷贝
    MiddleLayer(Data * data)
    :_pdata(data)
    {
        cout << "MiddleLayer(Data *)" << endl;
    }
    ~MiddleLayer(){
        cout << "~MiddleLayer()" << endl;
        if(_pdata){
            delete _pdata;
            _pdata = nullptr;
        }
    }

    Data * operator->(){
        return _pdata;
    }

    Data & operator*(){
        return *_pdata;
    }

private:
    Data * _pdata;
};
//三层ThirdLayer持有MiddleLayer，MiddleLayer持有Data
class ThirdLayer{
public:
    ThirdLayer(MiddleLayer * ml)
    :_pml(ml)
    {
        cout << "ThirdLayer(MiddleLayer *)" << endl;
    }
    ~ThirdLayer(){
        cout << "~ThirdLayer" << endl;
        if(_pml){
            delete _pml;
            _pml = nullptr;
        }
    }

    //箭头运算符
    //第三层的箭头返回值究竟是返回Data*，还是Data对象
    //返回第二层的对象或者指针呢？？
    MiddleLayer & operator->(){
        return *_pml;
    }
    //解引用运算符
    //返回值是什么呢？？？？
    MiddleLayer & operator*(){
        return *_pml;
    }

private:
    MiddleLayer * _pml;
};

void test(){
    //这是一个错误的用法，千万不要这么去用
    //为什么呢？？？不要去delete一个栈对象
    //会导致未定义行为
    //应该去持有堆对象
    MiddleLayer ml(new Data());
    ThirdLayer tl(&ml);
}

void test2(){
    ThirdLayer tl(new MiddleLayer(new Data()));
    tl->getData();
    //和下面的代码是等价的
    tl.operator->().operator->()->getData();

    //此时能否写出下面的代码呢？
    //(*tl).print();error不可以 解引用运算符不会递归调用
    (*(*tl)).getData();
    //和下面的代码是等价的
    tl.operator*().operator*().getData();
}

int main()
{
    test2();
    return 0;
}

