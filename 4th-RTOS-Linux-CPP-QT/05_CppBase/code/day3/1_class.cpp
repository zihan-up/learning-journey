#include <iostream>
using std::cout;
using std::endl;
//需要使用关键字class来标识是一个类
//后面是类名，一般建议是大写，对象、变量使用小写
//后面需要跟随着一组大括号，表示的是类所属的这块区域
//直接去定义一个类
class Person{

    void say(){

    }
    //类的{}中间区域可以编写对应的函数（成员函数）、属性（数据成员）

    int age;
    double height;
    double weight;

};//特别需要注意的是：结尾处需要有一个;


//也可以采取先声明，后定义的方式
class Student;


class Student{

};

void test(){

}

int main()
{
    test();
    return 0;
}

