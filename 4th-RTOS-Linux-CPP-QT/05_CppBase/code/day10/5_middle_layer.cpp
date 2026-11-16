#include <iostream>
using std::cout;
using std::endl;
//两层结构
class Data{
public:
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
    Data * get(){
        return _pdata;
    }
    //对箭头和解引用运算符进行重载
    //1.确定重载形式----成员
    //2.返回值是什么？Data *
    //3.函数的名称 固定operator->()/ operator*()
    //4.函数的形参----无
    Data * operator->(){
        return _pdata;
    }
    Data & operator*(){
        return *_pdata;
    }

private:
    Data * _pdata;
};

void test(){
    //只有new没有delete，但是居然没有内存泄漏
    MiddleLayer ml(new Data());
    //此时希望去调用Data的成员函数get()，应该怎么办？
    //这种写法完全可以，但是也可以使用另外的形式
    //ml.get()->getData();
    //下面的代码完全等价
    //写出57行代码时，编译器是按照58行进行处理的
    ml->getData();
    ml.operator->()->getData();
    //61行代码经过编译器处理过后，变成62行形式
    (*ml).getData();
    ml.operator*().getData();
}
void test2(){
    Data * data = new Data();


    delete data;
    data = nullptr;
}

void test3(){
    Data * data = new Data();

    MiddleLayer ml(data);

    delete data;
}

void test4(){
    //同样，也不可以将一个指针交给两个ml对象去管理
    //ml和ml2对象的析构函数中有delete的逻辑
    //delete两次
    Data * data = new Data();
    MiddleLayer ml(data);
    MiddleLayer ml2(data);
}

int main()
{
    test4();
    return 0;
}

