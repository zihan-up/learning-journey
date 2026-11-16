#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::for_each;
using std::copy;
using std::vector;
using std::ostream_iterator;

void func(int &value)
{
    ++value;
    cout << value << "  ";
}

void test()
{
    vector<int> vec = {1, 4, 7, 9, 2, 6, 11};
    /* for_each(vec.begin(), vec.end(), func); */
    //lambda表达式---->匿名函数
    for_each(vec.begin(), vec.end(), [](int &value){
             ++value;
             cout << value << "  ";
             });
    cout <<endl;

    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, "  "));
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
