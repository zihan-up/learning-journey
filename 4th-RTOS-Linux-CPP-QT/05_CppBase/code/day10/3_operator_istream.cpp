#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::cin;

class Complex{
public:
    Complex(int real, int image)
    :_real(real)
    ,_image(image)
    {

    }

    //输出流运算符

    friend ostream & operator<<(ostream & os, Complex & c);
    friend istream & operator>>(istream & is, Complex & c);
private:
    int _real;
    int _image;
};
//注意：输出流或者输入流运算符的返回值类型永远都是相同的
//无论是给哪个类对象进行重载
//第一个形参是ostream &或者istream &
//第二个参数取决于业务逻辑
//1 + 2i   1 -2i
ostream & operator<<(ostream & os, Complex & c){
    os << c._real;
    if(c._image > 0){
        os << "+";
    }
    os << c._image << "i";
    return os;
}
//输入流运算符重载
#if 0
istream & operator>>(istream & is, Complex & c){
    //is >> c;
    is >> c._real;
    is >> c._image;
    //上述是一种方式
    //还可以连续录入
    return is;
}
#endif
//这个版本的输入流运算符不是特别的健壮
//如果录入错误的单词会导致异常数据
//可以加入流的恢复机制
istream & operator>>(istream & is, Complex & c){
    //is >> c;
    //还可以连续录入   cin >> num >> num2;
    //默认的风格符是空格、换行、制表符
    is >> c._real >> c._image;
    return is;
}
void test2(){
    Complex c1(1, 2);
    cin >> c1;
    cout << c1 << endl;
}

void test(){
    Complex c1(1, 3);
    cout << c1 << endl;
    Complex c2(1, -4);
    cout << c2 << endl;
}

int main()
{
    test2();
    return 0;
}

