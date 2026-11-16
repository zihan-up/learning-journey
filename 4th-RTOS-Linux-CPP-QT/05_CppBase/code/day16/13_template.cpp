#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//需求：让大家实现一个类，实现比较器的功能
//比较器可以针对传递进来的这两个参数进行比较，比较是否相等
//普通类
class Comparator{
public:
    //成员函数模板
    template <class T>
    bool compare(T t1, T t2);
};
//如果类内部声明，外部定义
template <class T>
bool Comparator::compare(T t1, T t2){
    return t1 == t2;
}
void test(){
    Comparator comp;
    int a = 10, b = 20;
    cout << comp.compare(a, b) << endl;
    cout << comp.compare<double>(1.2, 1.2) << endl;
    cout << comp.compare("hello", "hello") << endl;
    cout << comp.compare<string>("hello", "hello") << endl;

    string s1 = "hello", s2 = "world";
    cout << comp.compare(s1, s2) << endl;

}

int main()
{
    test();
    return 0;
}

