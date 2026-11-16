#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
//现阶段的string使用的便是sso
void test(){

    int number = 10;
    cout << &number << endl;

    string s("hello");
    cout << (void *)s.c_str() << endl;

    string s2("hello,world");
    cout << (void *)s2.c_str() << endl;

    string s3("hello,world,hello,python");
    cout << (void *)s3.c_str() << endl;
}

int main()
{
    test();
    return 0;
}

