#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//采购：需要实时统计采购电脑的总金额
//就可以使用静态数据成员搭配着静态成员函数来一起使用
//每当我们采购一台电脑，那么总金额就需要实时统计出来
//构造函数中能否去访问静态数据成员？？？可以的。生命周期的先后来进行记忆
class Computer{
public:
    Computer(const char * brand, float price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        strcpy(_brand, brand);
        _totalPrice += _price;
    }

    //编写拷贝构造函数和赋值运算符函数
    //需要将_totalPrice的计算逻辑包含在里面

    static float getTotalPrice(){
        return _totalPrice;
    }


private:
    char * _brand;
    float _price;
    static float _totalPrice;
};
float Computer::_totalPrice = 0;


void test(){
    cout << Computer::getTotalPrice() << endl;
    Computer c1("apple", 12000);
    cout << Computer::getTotalPrice() << endl;
    Computer c2("huawei", 8000);
    cout << Computer::getTotalPrice() << endl;
}

int main()
{
    test();
    return 0;
}

