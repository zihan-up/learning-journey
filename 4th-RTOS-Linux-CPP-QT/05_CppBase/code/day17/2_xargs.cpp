#include <iostream>
using std::cout;
using std::endl;
//打印可变参数模板函数里面的参数内容
//提示出错，解决方案
//1.display无参函数
//2.display一参函数
//3.display一参模板函数
//===========================
void display(){
    cout << "display()" << endl;
}
template <class T>
void display(T t){
    cout << "display(T)"<< endl;
    cout << t << endl;
}
//中间这部分区域时我们设置的不同的出口
//============================


template <class T, class ...Args>
void display(T t, Args ...args){
    cout << t << endl;
    //args参数需要进行解包操作
    //解出一个参数，其他依然是压缩包的形式
    display(args...);
}


void test(){
    //函数调用时，把1传递给t，后面的三个参数打包传递给args
    //display函数内打印了1的内容，随后将其他三个参数解包操作
    //解出来一个参数，以及其他两个参数组成的压缩包，进一步调用display
    //随后又打印了第二个参数，剩下的两个参数又解包一次
    //调用display时，第一个参数传递给了t，第二个参数给args
    display(1, "hello", 10.3, true);
}

int main()
{
    test();
    return 0;
}

