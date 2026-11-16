#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;

void test(){
    unique_ptr<int> up(new int(20));
    cout << *up << endl;
    cout << up.get() << endl;
    //能否进行拷贝或者赋值操作呢？？
    //unique_ptr<int> up2(up);拷贝构造函数删除

    //移动构造、移动赋值运算函数可以
    //(unique_ptr && rhs)
    //这行代码底层究竟发生了什么事情？？？？
    //虽然此时不可以调用拷贝构造函数
    //但是可以调用移动构造函数
    unique_ptr<int> up2(std::move(up));
    cout << *up2 << endl;
    cout << up2.get() << endl;
    cout << up.get() << endl;
    cout << *up << endl;
}
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {}
    void print(){
        cout << _x << "," << _y << endl;
    }
private:
    int _x;
    int _y;
};

//作为容器的元素
void test2(){
    vector<unique_ptr<Point>> vec;
    unique_ptr<Point> up(new Point(0, 0));
    //vector存储数据是存储在栈还是存储在堆？？？堆
    //将up存入vector中，会调用拷贝构造函数
    //但是unique_ptr没有拷贝构造函数
    //如何解决呢？？？？？
    //1.可以直接传递一个右值
    //2.将一个左值转换成一个右值
    //vec.push_back(up);error这行有问题？？？？

    vec.push_back(unique_ptr<Point>(new Point(1, 2)));
    vec.push_back(std::move(up));
    cout << up.get() << endl;// 0
    //up->print();error丧失了对于堆空间的控制权
    //调用00的print
    vec[1]->print();
}

int main()
{
    test2();
    return 0;
}

