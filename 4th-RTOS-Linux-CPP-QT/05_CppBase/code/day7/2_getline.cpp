#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::string;

//使用getline函数，每次读取一行的数据
//相较于 >>每次只能够读取一个单词
void test(){
    ifstream ifs("hello.txt");
    if(!ifs){
        cerr << "this file is not found" << endl;
        return;
    }
    string line;
    //因为getline的返回值是istream对象
    //所以依然是可以将getline放置在while语句中的
    //返回值就是ifs对象本身，置于while、if语句中
    //依然会进行隐式的类型转换
    while(getline(ifs, line)){
        cout << line << endl;
    }
}
void test2(){
    ifstream ifs("hello.txt");
    if(!ifs.good()){
        cerr << "this file is not found" << endl;
        return;
    }
    string word;
    //会将文件输入流缓冲区里面的数据写入到word单词中
    //默认的分隔符是空格、换行符、制表符
    //所以每个单词会写一次
    while(ifs >> word){
        cout << word << endl;
    }
}

int main()
{
    test();
    return 0;
}

