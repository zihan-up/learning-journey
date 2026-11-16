#include <iostream>
using std::cout;
using std::endl;
//全局命名空间
//number就是属于全局命名空间下的
//如何访问呢？？两种方式
//1.直接访问  2::number来进行访问
int number = 10;


//匿名命名空间里面的实体不能够被外部程序访问到
//不可以跨文件访问
//如何访问呢？？？？
//1.直接访问  2::digit 来进行访问
namespace {
    int digit = 30;

} //end of namespace 

void test(){
    cout << number << endl;
    cout << ::number << endl;
    cout << digit << endl;
    cout << ::digit << endl;
}

int main()
{
    test();
    return 0;
}

