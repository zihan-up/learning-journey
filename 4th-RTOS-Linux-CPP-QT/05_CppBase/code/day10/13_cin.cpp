#include <iostream>
using std::cout;
using std::endl;
//实现一个非常简易的cin的功能，可以将cin放置在if、while等条件语句中
class Cin{
public:
    Cin(int good, int fail, int bad, int eof)
    :_good(good)
    ,_fail(fail)
    ,_bad(bad)
    ,_eof(eof)
    {}

    //编写一个类型转换函数
    operator bool(){
        return _good == 1;
    }

private:
    int _good;
    int _fail;
    int _bad;
    int _eof;
};
void test(){
    //Cin mycin(1, 0, 0, 0);
    Cin mycin(0, 1, 0, 0);
    if(mycin){
        cout << "cin is good" << endl;
    }else{
        cout << "cin is not good" << endl;
    }
}

int main()
{
    test();
    return 0;
}

