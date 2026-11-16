#include <iostream>

using std::cout;
using std::endl;

class Example
{
public:
    Example(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {}

    void print() const
    {
        _iy = 200;
        cout << "ix = " << _ix
             << ", iy = " << _iy
             << endl;
    }
private:
    int _ix;
    mutable int _iy;//可变的
};

void test()
{
    Example ex(100, 20);
    ex.print();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

