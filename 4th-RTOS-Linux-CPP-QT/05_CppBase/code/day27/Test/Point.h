#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

using std::cout;
using std::endl;

class Point
{
public:
    Point(int ix = 0, int iy = 0);
    ~Point();
    void print() const;

private:
    int _ix;
    int _iy;
    static int _iz;
};

/* int Point::_iz = 0; */
#endif
