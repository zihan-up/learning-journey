#include <iostream>
using std::cout;
using std::endl;
//公司的采购在进行电脑的采购工作
//希望去完成一个自动统计采购电脑总金额的功能
//采购每采购一台电脑，那么便创建、生成一个Computer对象
//需要做的事情便是实时统计采购电脑的总金额
//也就是说这个功能实际上在创建、生成这个Computer对象时就已经完成了
//静态数据成员如何进行初始化呢？？？需要在类的外部进行
//不需要再去写static关键字
class Computer{
public:
    static float _totalPrice;


private:
    char * _brand;
    float _price;
};
float Computer::_totalPrice = 0;


void test(){
    //如何访问静态数据成员呢？？？？？？
    //两种方式：1直接通过类名去访问(比较常用)  2，通过对象去访问
    //
    cout << Computer::_totalPrice << endl;
    Computer c;
    cout << c._totalPrice << endl;
}

int main()
{
    test();
    return 0;
}

