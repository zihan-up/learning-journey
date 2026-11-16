#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
//成员访问运算符
class Point{
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {

    }

    void print(){
        cout << _x << "," << _y <<endl;
    }

private:
    int _x;
    int _y;
};

class MiddleLayer{
public:
    MiddleLayer(Point * data)
    :_data(data)
    {

    }
    ~MiddleLayer(){
        if(_data){
            delete _data;
            _data = nullptr;
        }
    }

    Point * operator->(){
        return _data;
    }
    Point & operator*(){
        return *_data;
    }


private:
    Point * _data;
};

void test(){
    vector<Point> vec;
    vec.reserve(16);
    vec.push_back(Point(1, 2));
    vec.push_back(Point(3, 4));
    vec.push_back(Point(5, 6));
    //有一种遍历额方式叫做迭代器
    //迭代器你可以把它当做指针去使用
    //但是它并不是一个指针
    auto it1 = vec.begin();
    auto it2 = vec.end();
    while(it1 != it2){
        (*it1).print();
        it1->print();
        ++it1;
    }
}

void test2(){
    //可以把ml看做是一个指针，指向了Point对象
    MiddleLayer ml(new Point(1, 2));
    (*ml).print();
    ml->print();
}

int main()
{
    test2();
    return 0;
}

