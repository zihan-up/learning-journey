#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::cin;
//文件的输入输出功能
//使用键盘的录入功能，录入5个数字，并且存入文件中
//，随后读取文件的数据，将之前录入的数据显示出来
//思路：
//1.使用文件输入输出流对象fstream对象
//2.分别使用文件输入流和文件输出流来完成该功能
void test(){
    ofstream ofs("digit2.txt");
    int number;
    for(int i = 0; i < 5; ++i){
        cin >> number;
        ofs << number << " ";
    }
    //需要执行刷新缓冲区的操作
    ofs.flush();
    //构建一个文件输入流对象来读取文件里面的数据
    ifstream ifs("digit2.txt");
    number = 0;
    for(int i = 0; i < 5; ++i){
        ifs >> number;
        cout << number << " ";
    }
    cout << endl;
}

int main()
{
    test();
    return 0;
}

