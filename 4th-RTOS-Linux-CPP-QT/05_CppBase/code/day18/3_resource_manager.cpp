#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::endl;

//资源管理：如果一个开发者依然想使用C语言来进行文件的相关操作
//但是此时也是可以借助于一些C++的语法特性，能够让C语言
//更加的简单
//构造函数中托管资源
//析构函数中回收资源
class SafeFile{
public:
    SafeFile(FILE * fp)
    :_fp(fp)
    {}

    ~SafeFile(){
        if(_fp){
            fclose(_fp);
        }
    }

    void write(const string & content){
        fwrite(content.c_str(),1, content.size(), _fp);
    }
private:
    FILE * _fp;
};

void test(){

    SafeFile sf(fopen("hello.txt","a+"));
    sf.write("hello,world!!!!!!\n");
}

int main()
{
    test();
    return 0;
}

