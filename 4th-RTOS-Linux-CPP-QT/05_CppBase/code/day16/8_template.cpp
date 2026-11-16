#include <iostream>
using std::cout;
using std::endl;
//模板的声明的定义分开
template <class T>
T add(T t1, T t2);

void test(){
    int a = 10, b = 20;
    cout << add(a, b) << endl; 
}

template <class T>
T add(T t1, T t2){
    return t1 + t2;
}

void test2(){
    //要处理const char *字符串的相加
    const char * pstr1 = "hello";
    const char * pstr2 = "world";
    cout << add(pstr1, pstr2) << endl;
}

int main()
{
    test2();
    return 0;
}

