#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;
using std::string;

class Point
{
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int = 0, int = 0)" << endl;
    }

    ~Point()
    {
        cout <<"~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};

struct FILECloser
{
    void operator()(FILE *ptr) const
    {
        if(ptr)
        {
            fclose(ptr);
        }
    }
};

void test()
{
    //刷新缓冲区的方式：1、程序正常结束
    /* unique_ptr<Point> up(new Point(1, 2)); */
    unique_ptr<FILE, FILECloser> up(fopen("wd.txt", "a+"));
    string msg("hello, world\n");
    fwrite(msg.c_str(), 1, msg.size(), up.get());
    /* fclose(up.get()); */
}

void test2()
{
    shared_ptr<FILE> sp(fopen("wdsp.txt", "a+"), FILECloser());
    string msg("hello, world\n");
    fwrite(msg.c_str(), 1, msg.size(), sp.get());
}

int main(int argc, char *argv[])
{
    test2();
    return 0;
}

