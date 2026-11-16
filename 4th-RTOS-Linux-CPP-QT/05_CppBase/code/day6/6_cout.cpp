#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
//标准输出流，涉及到缓冲机制
void test(){
    //程序正常结束，缓冲区会刷新
    for(int i = 0; i < 1025; ++i){
        cout << 'a';
    }
}
void test2(){
    //缓冲区满，会导致立刻刷新缓冲区的数据
    //现象是：先输出1024个a.缓冲区只能够存储1024个a
    //休眠4秒钟之后，输出最后一个a，因为程序结束了
    for(int i = 0; i < 1025; ++i){
        cout << 'a';
    }
    sleep(4);
}
void test3(){
    //不加endl时，休眠4秒钟之后，输出了5个a
    //加上endl之后，立刻输出了5个a，休眠了4秒钟程序结束
    for(int i = 0; i < 5; ++i){
        cout << 'a' << endl;
    }
    sleep(4);
}

void test4(){
    //因为缓冲区大小是1024个字节
    //填满缓冲区并不会导致缓冲区立刻被刷新
    //只有下一次再次往缓冲区中写入数据时，才会刷新
    for(int i = 0; i < 1024; ++i){
        cout << 'a';
    }
    sleep(3);
    cout << 'b';
    sleep(2);
}

void test5(){
    //底层实际上便是调用了operator<<函数
    //该函数位于ostream头文件中
    //cout << 1时，调用该函数
    //__ostream_typ & operator<<(int __n)
    //cout.operator<<(1)返回值依然是cout对象本身
    //随后调用了out.operator<<(endl);
    //endl是什么呢？
    //inline basic_ostream & endl(basic_ostream & __os);
    cout << 1 << endl;
}

void test6(){
	cerr << 1;//没有缓冲区
	cout << 3;//有缓冲区
	sleep(2);
}

int main()
{
    test6();
    return 0;
}

