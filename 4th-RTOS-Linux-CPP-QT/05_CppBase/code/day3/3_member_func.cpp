#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//成员函数：类的内部定义
class Computer{
public:
    void setBrand(const char * brand){
        strcpy(_brand, brand);
    }
    void setPrice(float price){
        _price = price;
    }


private:
    char _brand[20];
    float _price;
};


void test(){
    Computer c;
    c.setBrand("Apple");
}

int main()
{
    test();
    return 0;
}

