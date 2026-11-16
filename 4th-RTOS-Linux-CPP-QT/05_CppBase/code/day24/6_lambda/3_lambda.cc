#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int gCnt = 12345;

void test()
{
    int num = 1;
    string name("wangdao");
    int age = 100;

    [num, name, age](int value){
        cout << "value = " <<value << endl;
        cout << "num = " << num << endl;
        cout << "name = " << name << endl;
        cout << "age = " << age << endl;
        cout << "gCnt = " << gCnt << endl;
    }(123);

    cout << endl << endl;
    //全部的外部局部变量是值捕获，可以采用=
    [=](int value){
        cout << "value = " <<value << endl;
        cout << "num = " << num << endl;
        cout << "name = " << name << endl;
        cout << "age = " << age << endl;
    }(123);

    cout << endl << endl;
    [&num, &name, &age](int value){
        cout << "value = " <<value << endl;
        ++num;
        cout << "num = " << num << endl;
        name = "wuhan";
        cout << "name = " << name << endl;
        age++;
        cout << "age = " << age << endl;
    }(123);

    cout << endl << endl;
    //全部的外部局部变量是引用捕获，可以采用&
    [&](int value){
        cout << "value = " <<value << endl;
        ++num;
        cout << "num = " << num << endl;
        name = "hubei";
        cout << "name = " << name << endl;
        age++;
        cout << "age = " << age << endl;
    }(123);

    cout << endl << endl;
    /* [&num, name, age](int value){ */
    [=, &num](int value){
        cout << "value = " <<value << endl;
        ++num;
        cout << "num = " << num << endl;
        cout << "name = " << name << endl;
        cout << "age = " << age << endl;
    }(123);

    cout << endl << endl;
    /* [&num, name, age](int value){ */
    [&, num](int value){
        cout << "value = " <<value << endl;
        cout << "num = " << num << endl;
        name = "lili";
        cout << "name = " << name << endl;
        age = 120;
        cout << "age = " << age << endl;
    }(123);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

