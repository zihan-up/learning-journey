#include <iostream>
using std::cout;
using std::endl;

class Computer{
public:
    //静态成员函数是不可以直接访问非静态的数据成员或者成员函数
    //如果实在希望访问，那么可以再静态成员函数的参数中传递一个对象
    //或者直接在静态成员函数处去创建一个对象，进而去访问
    //static void static_func(){
    static void static_func(Computer c){
        //因为它没有this指针，所以无法访问到非静态的数据成员
        //cout << _brand << _price << endl;error 
        //print();error 
        cout << _totalPrice << endl;
        cout << c._brand << endl;
        c.print();
    }
    static void static_func2(){
        Computer c;
        c.print();
    }

    //在非静态的成员函数中可以访问静态数据成员以及静态成员函数
    void print(){
        cout << _totalPrice << endl;
        static_func2();
        cout << "Computer::print" << endl;
    }

private:
    char * _brand;
    float _price;
    static float _totalPrice;
};
float Computer::_totalPrice = 0;


void test(){

}

int main()
{
    test();
    return 0;
}

