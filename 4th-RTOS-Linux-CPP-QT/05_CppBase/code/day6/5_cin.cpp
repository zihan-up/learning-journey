#include <iostream>
#include <string>
#include <limits>
using std::cout;
using std::endl;
using std::cin;
using std::string;
//cin输入流的使用
void check_stream_status(){
    cout << "good:" << cin.good()
        << "fail:" << cin.fail()
        << "bad:" << cin.bad()
        << "eof:" << cin.eof() << endl;
}
void test(){
    int number;
    check_stream_status();
    cin >> number;
    check_stream_status();
    cout << "录入一个数字" << endl;
    cout << number << endl;
    cout << "录入一个错误的信息，录入一个字符" << endl;
    //期望录入的是一个数字，但是我们却录入了一个字符串
    //导致了流的状态出现了问题，进入了failbit状态
    cin >> number;
    cout << number << endl;
    check_stream_status();
    //如果希望继续使用那么需要重置流的状态为good
    cin.clear();//恢复流的状态为good
    //ignore里面的两个参数表示的是清空1024个字节的缓冲区
    //如果在此期间遇到了\n，那么会提起结束
    //cin.ignore(1024, '\n');
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string word;
    cin >> word;
    cout << "输入的字符串为:" << word << endl;
}

void test2(){
    //循环录入一个整型数据，如果不是整型，则要求重新录入
    int number;
    while(1){
        cin >> number;
        if(cin.good()){
            cout << "录入的数字为:" << number << endl;
        }else if(cin.bad() || cin.eof()){
            break;
        }else{
            //fail状态
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "录入的数字有误，请重新录入" << endl;
        }
    }
}
void test3(){
    cout << "hello,world" << "hello" << endl;
    //背后究竟发生了什么事情呢？operator<<函数，返回值就是cout本身
    //cout.operator<<("hello,world").operator<<("hello");
    int number, number2;
    cin >> number >> number2;
    cout << number << endl;
    cout << number2 << endl;
    //(cin >> number) >> number2;
    //和上述完全是等价的，cin录入结束之后，返回的结果就是cin本身
    //cin.operator>>(number).operator>>(number2);
    //cin录入默认以空格符、换行符、制表符来作为分隔符

}

void test4(){
    int number;
    cin >> number;
    //令人不解的一点在于为什么可以把cin放置在if条件语句中
    //需要利用到后面介绍的运算符重载
    //把cin置于if条件语句中，会隐式转换为true或者false
    //表示的是当前流的状态是否是非fail
    if(cin){
        cout << "cin is good" << endl;
    }else {
        cout << "cin is bad" << endl;
    }
}
void test5(){
    int number;
    //1.cin >>录入结束之后，返回值其实就是cin对象本身
    //2.将cin放置在if条件条件语句中，会进行隐式类型转换
    if(cin >> number){
        cout << "cin is good" << endl;
    }else {
        cout << "cin is bad" << endl;
    }
   
}

int main()
{
    test5();
    return 0;
}

