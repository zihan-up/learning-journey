#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//定义一个Computer类
//建议是：成员函数写在上部；数据成员写在下部
//为了能够区分是数据成员还是函数里面的形参
//一般数据成员以_开头;形参直接编写对应的名称即可
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

    //属于类的内部
};

//属于类的外部
//默认修饰符是public；class的默认修饰符是private
//除此之外，基本是完全一致的
struct Person{
    int age;
};


void test(){
    //创建一个类对象
    //类其实就是用户的自定义的数据类型
    int number;
    Computer c;
    //c._price;error 
    c.setPrice(12000);

    Person p;
    p.age;
}

int main()
{
    test();
    return 0;
}

