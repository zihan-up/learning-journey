#include <iostream>
using std::cout;
using std::endl;
//函数模板和普通函数之间的重载
template <class T1, class T2>
T1 add(T1 t1, T2 t2)
{
return t1 + t2;
}

short add(short s1, short s2){
cout << "add(short,short)" << endl;
return s1 + s2;
}


void test(){
    short a = 10, b = 20;
    cout << add(a, b) << endl;

    int c = 30, d = 40;
    cout << add(c, d) << endl;
}

int main()
{
    test();
    return 0;
}

