#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::auto_ptr;

void test(){
    auto_ptr<int> ap(new int(10));
    cout << *ap << endl;
    cout << ap.get() << endl;
    //调用的是拷贝构造函数
    auto_ptr<int> ap2(ap);
    cout << *ap2 << endl;//10
    cout << ap.get() << endl;// 0
    cout << *ap << endl;//error
}

int main()
{
    test();
    return 0;
}

