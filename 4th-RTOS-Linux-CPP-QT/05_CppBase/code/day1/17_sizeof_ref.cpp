#include <iostream>
using std::cout;
using std::endl;

void test(){
    int number = 10;
    int & ref = number;
    int * p = &number;
    cout << sizeof(ref) << endl;//===sizeof(int)
    cout << sizeof(p) << endl; //指针所占用的空间
    cout << ref + 1 << endl;
    cout << p << endl;
    cout << p + 1 << endl;
}


int main()
{
    test();
    return 0;
}

