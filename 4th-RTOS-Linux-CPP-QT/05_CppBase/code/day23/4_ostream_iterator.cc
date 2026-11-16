#include <iostream>
#include <iterator>
#include <vector>

using std::cout;
using std::endl;
using std::ostream_iterator;
using std::vector;

void test()
{
    vector<int> vec = {1, 4, 8, 3, 5};
    ostream_iterator<int> osi(cout, "\n");
    copy(vec.begin(), vec.end(), osi);
    //operator<<
    /* cout << 1 << "\n"; */
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

