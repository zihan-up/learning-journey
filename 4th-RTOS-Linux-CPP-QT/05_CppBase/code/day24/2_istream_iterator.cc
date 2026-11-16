#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::istream_iterator;
using std::ostream_iterator;
using std::vector;
using std::copy;

void test()
{
    vector<int> vec;
    /* vec.reserve(10); */
    istream_iterator<int> isi(cin);
    /* copy(isi, istream_iterator<int>(), vec.begin()); */
    //std::back_inserter函数的底层会调用push_back
    copy(isi, istream_iterator<int>(), std::back_inserter(vec));

    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, "  "));
    cout << endl;
}

void test2()
{
    //vector在使用的时候，一定要有内存空间；如果没有或者不能自动扩容，
    //可能会有问题
    //其次，vector如果只有空间，没有对象，及时使用迭代器赋值，也不会
    //将对象传递到vector中
    vector<int> vec;
    vec.reserve(10);
    vec.push_back(20);
    *vec.begin() = 1;

    cout << "size() = " << vec.size() << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

