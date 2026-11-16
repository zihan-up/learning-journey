#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//赋值运算符形式探究
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
        cout << "Computer(const Computer &)" << endl;
        strcpy(_brand, rhs._brand);
    }
    //赋值运算符函数
    //完整的流程：四步走
    //1.自赋值判断
    //2.回收左操作数申请的堆空间
    //3.执行深拷贝操作
    //4.返回当前对象
    //Q1:返回值可以不是引用吗？？建议是引用
    //Q2：返回值可以是void吗？
    //Q3:形参一定要求是一个引用吗？建议引用，否则会出一次拷贝构造的调用
    //Q4:形参一定要求const吗？是，否则没法去处理右值的赋值操作
    //const Computer & rhs = Computer("ASUS", 10000);
    Computer & operator=(Computer & rhs){
    //void operator=(const Computer & rhs){
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
    c1 = c2;
    //c1.operator=(c2);
    c1.print();
    c2.print();
}

void test2(){
    //返回值如果是void没法去处理连续赋值的场景
    Computer c1("Apple",12000), c2("Huawei",7800), c3("Mi",6000);
    c1 = c2 = c3;
}
void test3(){
    Computer c1("Apple",12000), c2("Huawei",7800), c3("Mi",6000);
    c1 = Computer("ASUS", 10000);
}

int main()
{
    test();
    return 0;
}

