#include <iostream>
#include <fstream>
using std::cout;
using std::ifstream;
using std::endl;
using std::cerr;
//ifstream操作的是文件输入流缓冲区，该缓冲区会和硬盘上面的cpp.txt文件关联
//ifstream读取文件的数据之后，将指定下标的数据写入到了一个字符数组中
//读取指定下标位置区间里面的全部数据，将其写入到一个字符串中
//read函数 + seekg函数 + tellg函数
//比如用户输入的下标区间是0~100区间，首先应该先校验该区间是否有效、合理
//应当要求tellg的结果大于后区间
//使用read函数，读取指定长度的数据，写入到一个字符数组中
void test(){
    ifstream ifs("cpp.txt");
    if(!ifs){
        cerr << "this file is not found" << endl;
        return;
    }
    //表示的是用户指定的下标区间
    int beginIndex = 10;
    int endIndex = 30;
    //因为默认情况下，文件的游标是位于首位，所以需要将文件的游标
    //移动到文件的末尾
    ifs.seekg(0, std::ios_base::end);
    int length = ifs.tellg();
    if(endIndex > length || beginIndex > endIndex){
        cerr << "区间数值出错" << endl;
        return;
    }
    //此时文件的游标位于末尾，需要将文件的游标移动到beginIndex位置
    ifs.seekg(beginIndex);
    char * pstr = new char[endIndex - beginIndex + 1]();
    ifs.read(pstr, endIndex - beginIndex);
    cout << pstr << endl;
    delete [] pstr;
    pstr = nullptr;
}

//在上述的案例处理过程中，先将文件的指标移动到了末尾，再统计长度
//也可以使用ate模式，直接将游标定位到文件的末尾
void test2(){
    ifstream ifs("cpp.txt", std::ios_base::ate);
    if(!ifs){
        cerr << "this file is not found" << endl;
        return;
    }
    //表示的是用户指定的下标区间
    int beginIndex = 10;
    int endIndex = 30;
    //因为默认情况下，文件的游标是位于首位，所以需要将文件的游标
    //移动到文件的末尾
    //ifs.seekg(0, std::ios_base::end);
    int length = ifs.tellg();
    if(endIndex > length || beginIndex > endIndex){
        cerr << "区间数值出错" << endl;
        return;
    }
    //此时文件的游标位于末尾，需要将文件的游标移动到beginIndex位置
    ifs.seekg(beginIndex);
    char * pstr = new char[endIndex - beginIndex + 1]();
    ifs.read(pstr, endIndex - beginIndex);
    cout << pstr << endl;
    delete [] pstr;
    pstr = nullptr;
}

int main()
{
    test2();
    return 0;
}

