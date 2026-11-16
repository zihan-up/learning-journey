#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::function;

int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}

void test()
{
    int number = 100;
    /* auto f = [&number](int x){ */
    function<void(int)> f = [&number](int x){
        cout << "x = " << x << endl;
        ++number;
        cout << "number = " << number << endl;
    };

    f(123);
    f(1);
    f(23);
    cout << "number = " << number << endl;

    function<int(int, int)> f2 = add;


}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

