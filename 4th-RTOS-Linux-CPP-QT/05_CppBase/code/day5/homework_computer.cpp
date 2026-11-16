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

    //借助于已经采购的电脑，修改配置信息，也可以进行实时的统计
    //四步走：
    //1.自赋值判断
    //2.回收左操作数申请的堆空间
    //3.执行深拷贝操作
    //4.返回对象
    //电脑的总金额应如何变化？？？
    //之前采购了一台小米5000，现在变成了Macbook 12000
    Computer & operator=(const Computer & rhs){
        if(this != &rhs){
            delete [] _brand;
            _brand = new char[strlen(rhs._brand) + 1]();
            strcpy(_brand, rhs._brand);
            //减去原先的价格
            _totalPrice -= _price;
            _price = rhs._price;
            _totalPrice += _price;
        }
        return *this;
    }

    //目前已经采购了某台电脑，复制当前电脑信息，采购了一台同样配置的电脑
    Computer(const Computer & rhs)
    :_brand(new char[strlen(rhs._brand) + 1]())
    ,_price(rhs._price)
    {
        strcpy(_brand, rhs._brand);
        _totalPrice += _price;
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
    Computer c3("Mi", 5400);
    cout << Computer::getTotalPrice() << endl;
    c3 = c1;
    cout << Computer::getTotalPrice() << endl;
    Computer c4 = c3;
    cout << Computer::getTotalPrice() << endl;
}

int main()
{
    test();
    return 0;
}

