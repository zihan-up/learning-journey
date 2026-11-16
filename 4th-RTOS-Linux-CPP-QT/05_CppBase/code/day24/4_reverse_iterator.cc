#include <iostream>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::reverse_iterator;

void test0()
{
    vector<int> vec = {1, 3, 5, 7, 11, 10, 5};
    vector<int>::iterator it = vec.begin();
    for(; it != vec.end(); ++it)
    {
        cout << *it << "  ";
    }
    cout << endl;
}

void test()
{
    vector<int> vec = {1, 3, 5, 7, 11, 10, 5};
    vector<int>::reverse_iterator rit = vec.rbegin();
    for(; rit != vec.rend(); ++rit)
    {
        cout << *rit << "  ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

