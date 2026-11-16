#include <iostream>
//引入c++的头文件，c++头文件和c语言的头文件最明显的特征是没有后缀名
//头文件默认位于/usr/include/c++/11
//下面的代码表示的是c++里面的名称空间/命名空间
//c++标准类库里面的所有的组件、功能都是位于std命名空间中的
//命名空间简单理解为是相当于姓氏一样，公司的名称一样
//cout这个对象可能很多公司都有，如果这些公司的这些对象被一个项目
//同时使用，那么cout究竟指的是哪个公司的呢？？加上公司名称的前缀就可以区分
using std::cout;
using std::endl;

void test(){
    //使用cout对象来进行字符串的输出功能，最后末尾添加endl换行功能
    //等价于printf("hello,world\n")
    //其中 << 表示的是一个函数，这是一个简写
    //实际上表示的是
    //cout.operator<<("hello,world").operator<<(endl);
    //编译器会将下面写的代码转换成上面的代码形式
    //该函数的名称就是operator<<
    cout << "hello,world" << endl;
    cout << 1 << endl;
    printf("hello,world\n");
}
//main函数是程序的入口，进一步调用了test函数
int main()
{
    test();
    return 0;
}

