#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::map;

struct CompareMap
{
    bool operator()(const int &lhs, const int &rhs) const
    {
        cout << "struct CompareMap" << endl;
        return lhs <= rhs;
    }
};
void test()
{
    map<int, int, CompareMap> number;
    number[1] = 10;
    number[1] = 20;

    cout << "number.size() = " << number.size() << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

