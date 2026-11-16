#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;

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
    friend bool operator<(const Point &lhs, const Point &rhs);
    friend struct ComparePoint;

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

//运算符的重载
bool operator<(const Point &lhs, const Point &rhs)
{
    cout << "bool operator<" << endl;
    if(lhs.getDistance() < rhs.getDistance())
    {
        return true;
    }
    else if(lhs.getDistance() == rhs.getDistance())
    {
        if(lhs._ix < rhs._ix)
        {
            return true;
        }
        else if(lhs._ix == rhs._ix)
        {
            if(lhs._iy < rhs._iy)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//函数对象的写法
struct ComparePoint
{
    bool operator()( const Point& lhs, const Point& rhs ) const
    {
        /* cout << "struct ComparePoint" << endl; */
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs._ix < rhs._ix)
            {
                return true;
            }
            else if(lhs._ix == rhs._ix)
            {
                if(lhs._iy < rhs._iy)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};


namespace std
{

template <>
struct less<Point>
{
    bool operator()( const Point& lhs, const Point& rhs ) const
    {
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs.getX() < rhs.getX())
            {
                return true;
            }
            else if(lhs.getX()== rhs.getX())
            {
                if(lhs.getY()< rhs.getY())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

}//end of namespace std

void test()
{
    vector<Point>  vec = {
        Point(1, 2),
        Point(-1, 2),
        Point(1, -2),
        Point(-1, -2),
        Point(1, 2),
        Point(3, 2),
    };
    priority_queue<Point, std::vector<Point>, ComparePoint> number;

    for(size_t idx = 0; idx != vec.size(); ++idx)
    {
        number.push(vec[idx]);
        cout << "优先级最高的元素: " << number.top() << endl;
    }
    cout << endl;

    while(!number.empty())
    {
        cout << number.top() << "  ";
        number.pop();
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

