#include <iostream>
using std::cout;
using std::endl;
//默认参数的设置顺序
//是严格从右往左进行的
//如果某个形参设置了默认值，那么该形参右边的参数必须都设置默认值
void func(int a = 0, int b = 0, int c = 0, int d = 0){

}
void func(){

}
//设置了默认参数之后，可以形成一系列的重载函数
//所以设置了默认参数之后，那么函数重载需要特别留意，防止冲突
void test(){
    //函数的参数匹配是从左往右进行匹配的
    func(1, 2, 3, 4);
    func(2, 3, 4);
    func(3, 4);
    func(5);
    func();
}

int main()
{
    test();
    return 0;
}

