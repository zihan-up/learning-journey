#include <iostream>
using std::cout;
using std::endl;
//可变参数模板
//其中Args类比为之前的T，args类比为之前的t
template <class ...Args>
//这个功能非常像压缩包
void display(Args ...args){
    //希望统计一共有多少个参数
    //Args个数和args个数应当是一致的
    //cout << sizeof(...args) << endl;
    cout << sizeof...(args) << endl;
}

void test(){
    //Args:int、double、bool、char *
    //args：1、10.5、true、hello
    display(1, 10.5, true, "hello");
}
//既然有打包操作，肯定有解包操作
//类似于电脑中的winrar压缩工具
//...如果在args参数的左边表示的是打包，
//如果在args参数的右边表示的是解包

//需要将所有的参数进行打包之后，调用print函数
template <class ...Args>
void print(Args ...args){
    //args...一次性从包中解压出来一个参数，其他参数依然是打包的形式
}

int main()
{
    test();
    return 0;
}

