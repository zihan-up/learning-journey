#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    //数据成员的初始化并不取决于其在初始化列表中的顺序
    //而是取决于在声明时的顺序
    //为了减少错误的产生，强烈建议初始化列表中的顺序和声明的顺序一致
    //问题1：_x和_y谁先会被初始化呢？？_x
    //并不是说在初始化列表的前面就会被先初始化，而是取决于声明顺序
    //因为先声明_x后声明_y
    //所以会先给_x(_y)进行初始化，但是此时_y还没有被初始化
    //随后再用value给_y进行初始化
    Point(int value)
    :_y(value)
    ,_x(_y)
    {
        cout << "Point(value)" << endl;
    }



//private:
//声明的顺序在这
    int _x;
    int _y;
};



void test(){
    Point pt(3);
    cout << pt._x << ":" << pt._y << endl;
}

int main()
{
    test();
    return 0;
}

