#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

//进行二者类型的转换，不仅可以使用类型转换函数，还可以使用
//特定形式的构造函数、赋值运算符

class CNY;
class USD{
public:
    USD(double value)
    :_value(value)
    {
        cout << "USD(double)" << endl;
    }
    friend class CNY;
    //类型转换函数
    operator CNY() const;
    friend ostream & operator<<(ostream & os, USD & usd);

private:
    double _value;
};

class CNY{
public:
    CNY(double value)
    :_value(value)
    {
        cout << "CNY(double)" << endl;
    }

    //CNY中提供一个特殊形式的构造函数
    CNY(USD & usd)
    :_value(usd._value * 7.2)
    {
        cout << "CNY(const USD &)" << endl;
    }


    //类型转换函数
    operator USD(){
        return _value / 7.2;
    }

    //赋值运算符  将usd转换成cny
#if 0
    CNY & operator=(const USD & usd){
        cout << "CNY::operator=(const USD &)" << endl;
        _value = usd._value * 7.2;
        return *this;
    }
#endif

    friend ostream & operator<<(ostream & os, CNY & cny);

private:
    double _value;
};

//将usd转换成cny
USD::operator CNY() const{
    cout << "USD::operatorCNY" << endl;
    return _value * 7.2;
}
//对于usd和cny输出流运算符进行重载
ostream & operator<<(ostream & os, USD & usd){
    os << "$"<< usd._value ;
    return os;
}
ostream & operator<<(ostream & os, CNY & cny){
    os << "￥" << cny._value ;
    return os;
}

//结论：如果特殊形式的构造函数和类型转换函数同时存在的情况下
//优先选择类型转换函数，其次才会去选择特殊形式的构造函数
void test(){
    USD usd(100);
    cout << usd << endl;
    //下面代码如果写成赋值运算符，写在哪个类中？？？CNY中
    CNY cny = usd;//在usd中设置转换为CNY的函数
    cout << cny << endl;
}

//结论：当赋值运算符和类型转换函数、特殊形式的构造函数同时存在的情况下
//优先选择赋值运算符来进行操作，其次选择类型转换函数，最后选择构造函数
void test2(){
    USD usd(100);
    CNY cny(100);
    cout << usd << endl;
    //下面代码如果写成赋值运算符，写在哪个类中？？？CNY中
    cny = usd;//在usd中设置转换为CNY的函数
    cout << cny << endl;
}

int main()
{
    test2();
    return 0;
}

