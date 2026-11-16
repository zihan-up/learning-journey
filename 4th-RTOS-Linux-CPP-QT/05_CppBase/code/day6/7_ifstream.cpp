#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
void check_stream_status(ifstream & ifs){
    cout << "ifs.goodbit:" << ifs.good()
        << "ifs.failbit:" << ifs.fail()
        << "ifs.eofbit:" << ifs.eof()
        << "ifs.badbit:" << ifs.bad() << endl;
}

void test(){
    //ifstream ifs = "1.txt";explicit禁止上述这个行为产生
    //1.无参构造函数
    ifstream ifs;
    ifs.open("1.txt");
    //尤其是文件输入流，流的状态非常容易出错，比如文件不存在
    check_stream_status(ifs);
    if(!ifs){
        cerr << "file is not found" << endl;
    }
    //2.使用有参构造函数
    ifstream ifs2("2.txt");
    if(!ifs2){
        cerr << "file is not found" << endl;
    }
}

void test2(){
    ifstream ifs("hello.txt");
    if(!ifs){
        cerr << "the file is not found" << endl;
        return;
    }
    string word;
    //ifs读取数据写入到word中
    //每次读取一个单词，分割符默认是空格、换行、制表符
    while(ifs >> word){
        cout << word << endl;
    }
}

int main()
{
    test2();
    return 0;
}

