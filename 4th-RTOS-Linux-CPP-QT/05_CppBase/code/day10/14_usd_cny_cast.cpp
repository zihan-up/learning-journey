#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class CNY;
class USD{
public:
    USD(double value)
    :_value(value)
    {
        cout << "USD(double)" << endl;
    }
    //类型转换函数
    operator CNY();
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

    //类型转换函数
    operator USD(){
        return _value / 7.2;
    }

    friend ostream & operator<<(ostream & os, CNY & cny);

private:
    double _value;
};

//将usd转换成cny
USD::operator CNY(){
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

void test(){
    USD usd(100);
    cout << usd << endl;
    CNY cny = usd;//在usd中设置转换为CNY的函数
    cout << cny << endl;
    cout << "===============" << endl;
    CNY cny2(100);
    cout << cny2 << endl;
    USD usd2 = cny2;//在cny中设置转换为usd的函数
    cout << usd2 << endl;
}

int main()
{
    test();
    return 0;
}

