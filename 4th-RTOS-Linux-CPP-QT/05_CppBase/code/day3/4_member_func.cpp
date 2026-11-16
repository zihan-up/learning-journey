#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//成员函数：类的内部声明，外部定义
class Computer{
public:
    void setBrand(const char * brand);

    void setPrice(float price);


private:
    char _brand[20];
    float _price;
};

//放到外部去实现
//成员函数需要使用类名::标识当前的函数属于类的成员函数
//函数的定义虽然是写在类的外部，但是访问类里面的私有数据成员
//依然是可以访问到的
void Computer::setBrand(const char * brand){
    strcpy(_brand, brand);
}
void Computer::setPrice(float price){
    _price = price;
}


void test(){
    Computer c;
    c.setBrand("Apple");
}

int main()
{
    test();
    return 0;
}

