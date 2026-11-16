#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//以Computer为例，探讨赋值运算符的写法有没有问题
class Computer{
public:
    Computer(const char * brand, float price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        strcpy(_brand, brand);
    }
    //必须显示写出析构函数
    ~Computer(){
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
        }
    }
    //拷贝构造函数也是有问题的，需要自主写出来
    Computer(const Computer & rhs)
    :_brand(new char[strlen(rhs._brand) + 1]())
    ,_price(rhs._price)
    {
        strcpy(_brand, rhs._brand);
    }
    //赋值运算符函数
    //完整的流程：四步走
    //1.自赋值判断
    //2.回收左操作数申请的堆空间
    //3.执行深拷贝操作
    //4.返回当前对象
    Computer & operator=(const Computer & rhs){
        //左操作数应当先执行堆空间的回收操作
        //再去执行深拷贝操作
        if(this != &rhs){
            delete [] _brand;
            _brand = new char[strlen(rhs._brand) + 1]();
            strcpy(_brand, rhs._brand);
            _price = rhs._price;
        }
        return *this;
    }

    void print(){
        cout << "_brand=" << _brand << ",_price=" << _price << endl;
    }



private:
    char * _brand;
    float _price;
};


void test(){
    Computer c1("Apple", 12000), c2("Huawei",7800);
    c1.print();
    c2.print();
    c1 = c2;
    c1.print();
    c2.print();
    //考虑一些极端情况
    c1 = c1;
    c1.print();
}

int main()
{
    test();
    return 0;
}

