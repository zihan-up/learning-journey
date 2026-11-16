#include <cmath>
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::pair;
using std::make_pair;

template <typename Container>
void display(const Container &con)
{
    for(auto &elem : con)
    {
        cout << elem.first << "  "
             << elem.second << endl;
    }
}

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
    }

    double getDistance() const
    {
        return hypot(_ix, _iy);
    }

    int getX() const
    {
        return _ix;
    }

    int getY() const
    {
        return _iy;
    }

    ~Point()
    {}

    friend std::ostream &operator<<(std::ostream &os, const Point &rhs);

private:
    int _ix;
    int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs)
{
    os << "(" << rhs._ix
       << ", " << rhs._iy
       << ")";

    return os;
}

void test()
{
    unordered_map<string, Point> number = {
        {"beijing", Point(1, 2)},
        {"nanjing", Point(-1, 2)},
        pair<string, Point>("beijing", Point(1, -2)),
        pair<string, Point>("dongjing", Point(1, -2)),
        make_pair("wuhan", Point(1, 2)),
        make_pair("hubei", Point(-1, -2))
    };
    display(number);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

