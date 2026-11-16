#include <iostream>
#include <sstream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
//字符串输出流的使用
void test(){
    int number = 10;
    int number2 = 20;
    string key = "tom";
    // number = 10,number2 = 20, key = tom
    ostringstream oss;
    oss << "number=" << number << ",number2 = " << number2 << ",key = " << key << endl;
    cout << oss.str() << endl;
}

int main()
{
    test();
    return 0;
}

