#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//字符数组、字符指针
void test(){
    //字符数组
    char str[6] = "hello";
    char str2[6] = {'h','e','l','l','o'};
    char str3[] = "hello";
    cout << str << ":" << str2 << ":" << str3 << endl;
    //字符数组：修改字符串的值、变更新的指向
    str[0] = 'H';
    cout << str << endl;
    //str2 = "world";error 
    //因为数组名称代表的是数组首元素的地址，如果指向了一个新的元素
    //那么现在的这个数组就无法指向了，后续操作系统也无法进行回收
}

void test2(){
    const char * pstr = "hello";
    //pstr[0] = 'H';error 不可以修改字符串的值
    pstr = "world"; //变更指向
    cout << pstr << endl;
}

//作业：根据下面的代码尝试画出对应的内存图示
void test3(){
    //指针指向堆区 末尾留一位给\0
    char * pstr = new char[5 + 1]();
    strcpy(pstr, "hello");
    cout << pstr << endl;
    pstr[0] = 'H';
    cout << pstr << endl;
    delete [] pstr;
    //指向新的字符串
    pstr = new char[15]();
    strcpy(pstr, "hello,world");
    cout << pstr << endl;

    delete [] pstr;
    pstr = nullptr;
}

void test4(){
    //求解字符串的长度 应该使用strlen
    char str[6] = "hello";
    const char * pstr = "hello";
    cout << sizeof(str) << endl; //6
    cout << sizeof(pstr) << endl; //8
    cout << strlen(str) << endl; //5
    cout << strlen(pstr) << endl; //5
}

void test5(){
    //字符串的拼接
    //字符数组、字符指针
    //先看特殊的，指向常量区的字符指针
    const char * pstr1 = "hello";
    const char * pstr2 = "world";
    //此时可以指向堆区
    char * pstr = new char[strlen(pstr1) + strlen(pstr2) + 1]();
    strcpy(pstr, pstr1);
    strcat(pstr, pstr2);
    cout << pstr << endl;
    delete [] pstr;
    pstr = nullptr;
    cout << "======================" << endl;
    char str1[6] = "hello";
    char str2[6] = "world";
    //此时可以使用字符数组，使用字符指针指向堆区
    char str3[11];
    strcpy(str3, str1);
    strcat(str3, str2);
    cout << str3 << endl;
}

int main()
{
    test5();
    return 0;
}

