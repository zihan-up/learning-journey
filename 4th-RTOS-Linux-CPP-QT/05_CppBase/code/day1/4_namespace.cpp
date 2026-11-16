#include <iostream>
using std::cout;
using std::endl;
//命名空间的相互调用
//此时采用一种前向声明的方式
namespace wd{
    void display();
    void show();
}// end of namespace wd 

namespace wh{
void print(){
    cout << "wh::print" << endl;
}
void show(){
    cout << "wh::show" << endl;
    wd::display();
}
} //end of namespace wh


namespace wd{
void display(){
    cout << "wd::display" << endl;
    wh::print();
}
void show(){
    cout << "wd::show" << endl;
    wh::show();
}
}// end of namespace wd 


void test(){
    wd::show();
}

int main()
{
    test();
    return 0;
}

