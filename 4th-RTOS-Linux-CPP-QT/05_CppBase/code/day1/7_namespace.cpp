#include <iostream>
using std::cout;
using std::endl;
//命名空间的嵌套使用
namespace wd{
    int person = 20;

    void display(){
        cout << "wd::display" << endl;
    }

    namespace cpp{
        int count = 10;
        void func(){
            cout << "wd::cpp::func" << endl;
        }
    }// end of namespace cpp 
}// end of namespace wd 
using wd::person;
using wd::display;

void test(){
    cout << person << endl;
    display();
}

void test2(){
    //作用域限定符的方式
    cout << wd::cpp::count << endl;
    wd::cpp::func();
}
//using编译指令
using namespace wd;
void test3(){
    cout << cpp::count << endl;
}

void test4(){
    //using声明机制
    using wd::cpp::count;
    using wd::cpp::func;
    cout << count << endl;
    func();
}

int main()
{
    test4();
    return 0;
}

