#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

class OS{
public:
    // const string & file = "hello";
    // 底层便是利用到了没有标注explicit(构造函数)
    // 利用构造函数来完成了上述的隐式类型转换
    OS(const string & file){

    }
};


void test(){
    OS os("hello");
}

void test2(){
    //文件输出流的使用
    //1.借助于构造函数创建一个ofstream对象
    ofstream ofs;
    //文件输出流和外部的文件进行绑定
    //位于文件输出流对象里面的数据最终会写入到文件中
    ofs.open("dest.txt"); 
    //Q:对于文件输入流来说，文件不存在，会怎么样？会报错
    //对于文件输出流来说，文件不存在，会怎么样？直接创建新的
    //有的框架，还有额外的规定，要求输出的时候，文件必须不存在
    //如果文件存在，直接报错 hadoop
    //2.借助于有参构造函数直接创建一个和文件进行关联的ofstream对象
    ofstream ofs2("dest2.txt");
    //if(ofs2){}这个代码不需要写，没有必要
}

void test3(){
    ofstream ofs("dest.txt");
    //在标准输出流中有这种写法，那么在文件输出流中也有这种写法
    //如果多次执行当前函数，那么文件中也是自始至终只有一行数据
    //主要的原因是此时默认情况下是覆盖写操作
    //如果你希望能够如实记录每一次写入的信息，那么需要设置为追加写
    //操作
    ofs << "hello,world" << endl;
}

void test4(){
    //实现追加写的效果
    ofstream ofs("wd.txt", std::ios_base::app);
    ofs << "hello,world" << endl;
    ofs.close();
}

//除了使用<<符号之外，还可以使用write函数来执行写操作
void test5(){
    //1.创建ofs对象
    ofstream ofs("ofs.txt", std::ios_base::app);
    char arr[20] = "gooooooo\n";
    ofs.write(arr, strlen(arr));

    string content = "hello,world,hello c++;hello python";
    //要点：将c++里面的string转换成c风格的字符串
    ofs.write(content.c_str(), content.size());
    ofs.close();
}

int main()
{
    test5();
    return 0;
}

