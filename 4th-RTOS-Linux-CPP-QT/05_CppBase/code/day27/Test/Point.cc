#include "Point.h"

int Point::_iz = 0;

Point::Point(int ix , int iy )
: _ix(ix)
, _iy(iy)
{

}

Point::~Point()
{

}

void Point::print() const
{
    cout << "ix = " << _ix << endl
         << "iy = " << _iy << endl
         << "iz = " << _iz << endl;
}
