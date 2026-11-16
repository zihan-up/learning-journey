#include <iostream>
using std::cout;
using std::endl;

class FunctionObj{
public:
    //函数调用运算符
    //返回值：可以根据具体的业务场景来进行确定
    //函数的名称：operator()
    //函数的参数：根据具体的业务场景来确定
    void operator()(){
        cout << "operator()()" << endl;
    }
    void operator()(int a, int b){
        cout << "operator()(int,int)" << endl;
    }
};


void test(){
    FunctionObj fo;
    //本质上来说，其实就是在调用成员函数
    //那么它和成员函数之间的区别在哪呢？？？？
    //区别挺微弱的
    //函数调用运算符：该对象里面只有唯一的一个功能
    //那就是函数调用运算符函数
    //成员函数：该对象中有很多的成员函数，有众多功能
    fo();
    fo(1, 2);
}


//是否比某个数要大
class IsGreatThan{
public:
    IsGreatThan(int value)
    :_threshold(value)
    {
    }
    //这个类中只有唯一的一个功能便是比较大小
    //函数调用运算符
    bool operator()(int value){
        return value > _threshold;
    }

private:
    //阈值
    int _threshold;
};

void test2(){
    IsGreatThan igt(10);
    cout << igt(8) << endl;
    cout << igt(20) << endl;
}

int main()
{
    test2();
    return 0;
}

