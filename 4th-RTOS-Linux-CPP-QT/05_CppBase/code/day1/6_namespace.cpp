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

using namespace wd;

void test(){
    //2.using namespace wd;
    cout << person << endl;
    display();
}

int main()
{
    test();
    return 0;
}

