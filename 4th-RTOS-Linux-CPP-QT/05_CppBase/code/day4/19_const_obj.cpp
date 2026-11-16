#include <iostream>
using std::cout;
using std::endl;
//对象的组织：使用类对象基本上和使用内置数据类型是一样的
class Point{
public:
    Point(int x = 0, int y = 0)
    :_x(x)
    ,_y(y)
    {

    }
    void print(){
        cout << "Point::print" << endl;
    }
    void print() const {
        cout << "Point::print const" << endl;
    }

    void display() const {
        cout << "Point::display const" << endl;
    }
    void show(){
        cout << "Point::show" << endl;
    }
 
private:
    int _x;
    int _y;
};
void test(){
    //对比内置数据类型和自定义类对象使用
    int number;
    Point pt;
    const int number2 = 5;
    const Point pt2(1, 2);
    int * pInt = new int(10);
    Point * p = new Point(1, 2);
}

void test2(){
    //整个对象都是不可以改变的
    //普通的成员函数怎么能够保证不会修改数据成员呢？？？
    //只有const成员函数可以保证
    const Point pt(1, 2);
    pt.print();
}

void test3(){
    //设计两个对象，一个是const对象，一个是非const对象
    //设计两个成员函数，一个是const成员函数，一个是非const成员函数
    const Point pt(1, 2);
    Point pt2(3, 4);
    pt.print();//const对象调用const版本
    pt2.print();//非const对象调用非const版本
    cout << "-------display-----" << endl;
    pt.display();
    pt2.display();//非const对象可以调用const成员函数
    cout << "-------show---------" << endl;
    pt.show();//const对象不可以调用非const成员函数
    pt2.show();
}

int main()
{
    test3();
    return 0;
}

