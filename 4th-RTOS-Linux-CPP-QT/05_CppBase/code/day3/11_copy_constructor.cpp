#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer{
public:
    //指针数据成员，在近几天全部都使用深拷贝的形式
    Computer(const char * brand, float price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char *, float)" << endl;
    }
    //因为构造函数中执行了new操作，所以此时必须得主动写出析构函数
    ~Computer(){
        cout << "~Computer(" << _brand << endl;
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
        }
    }
    //拷贝构造函数
    //推断此时编译器给Computer生成的拷贝构造函数是什么样的？
#if 0
    编译器默生成的版本，属于浅拷贝
    Computer(const Computer & rhs)
    :_brand(rhs._brand)//就是属于浅拷贝
    ,_price(rhs._price)
    {
        cout << "Computer(const Computer &)" << endl;
    }
#endif
    //需要进行深拷贝，涉及到了指针数据成员
    //并不是说凡是涉及到了指针数据成员一定要进行深拷贝
    //而是目前阶段，指针数据成员进行深拷贝是最优解
    //Computer c2(c1);
    Computer(const Computer & rhs)
    :_brand(new char[strlen(rhs._brand) + 1]())
    ,_price(rhs._price)
    {
        strcpy(_brand, rhs._brand);
        cout << "Computer(const Computer & rhs)" << endl;
    }



    void print(){
        cout << "_brand=" << _brand << ",_price=" << _price << endl;
    }
private:
    char * _brand;
    float _price;
};


void test(){
    Computer c1("Apple", 12000);
    Computer c2 = c1;
    //Computer c2("Apple", 12000);
    c2.print();
}

int main()
{
    test();
    return 0;
}

