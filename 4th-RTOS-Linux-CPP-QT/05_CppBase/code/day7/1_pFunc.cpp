#include <iostream>
using std::cout;
using std::endl;

inline
basic_ostream & endl(basic_ostream & __os){

}


void test(){
//函数指针的使用
//定义一个函数指针去指向endl函数
 basic_ostream & (*pFunc)(basic_ostream &);
 pFunc = endl;
 //operator<<
 
 operator<<(pFunc);
 operator<<(endl);
 cout << 1 << endl;

}

int main()
{
    test();
    return 0;
}

