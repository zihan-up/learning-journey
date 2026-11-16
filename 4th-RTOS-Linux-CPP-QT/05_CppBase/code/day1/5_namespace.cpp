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


void test(){
    //希望去访问外层的命名空间里面的实体
    //1.作用域限定
    cout << wd::person << endl;
    wd::display();
    //2.using namespace wd;
}

int main()
{
    test();
    return 0;
}

