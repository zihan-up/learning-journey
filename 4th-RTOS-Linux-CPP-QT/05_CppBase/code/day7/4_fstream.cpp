#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::fstream;
using std::cin;
//文件的输入输出功能
//使用键盘的录入功能，录入5个数字，并且存入文件中
//，随后读取文件的数据，将之前录入的数据显示出来
//思路：
//1.使用文件输入输出流对象fstream对象
//2.分别使用文件输入流和文件输出流来完成该功能
//最终我们发现无法从文件中读取到任何数据,为什么呢？
//因为使用fstream进行写操作时，此时文件的游标已经位于文件的末尾了
//后续再次读取的时候，游标依然位于文件的末尾
//读取不到任何的数据，如果希望能够读取到数据，需要将文件的游标移动到
//文件的开始位置
void test(){
    fstream fs("digit.txt");
    int number;
    int number2;
    for(int i = 0; i < 5; ++i){
        cin >> number;
        fs << number << " ";
    }
    fs.flush();
    for(int i = 0; i < 5; ++i){
        fs >> number2;
        cout << "读取到:" <<  number2 << endl;
    }
}
//设置文件的游标，
//一种设置绝对坐标:
//一种是设置相对坐标
//如果设置到文件的开始位置，无论哪种方式都比较方便
//seekg(0) seekg(0,std::ios_base::beg)
//如果此时需要设置到文件的末尾，很明显第二种方式更为方便
//seekg(tellg统计出长度) seekg(0, std::ios_base::end)
void test2(){
    fstream fs("digit.txt");
    int number;
    for(int i = 0; i < 5; ++i){
        cin >> number;
        fs << number << " ";
    }
    //执行完了写操作，此时文件的游标位于末尾的位置
    //此时需要将文件游标移动到文件的开始位置
    //设置文件游标的两种方式都是可以的
    //fs.seekg(0);
    fs.seekg(0, std::ios_base::beg);
    for(int i = 0; i < 5; ++i){
        fs >> number;
        cout << number << " ";
    }
    cout << endl;
}

int main()
{
    test2();
    return 0;
}

