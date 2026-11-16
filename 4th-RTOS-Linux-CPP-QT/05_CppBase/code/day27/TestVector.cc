#include "Vector.h"
#include <iostream>

using std::cout;
using std::endl;

void displayCapacity(const Vector<int> &con)
{
    cout << "size() = " << con.size() <<endl;
    cout <<"capacity() = " << con.capacity() << endl;
}
void test()
{
    Vector<int> vec;
    displayCapacity(vec);

    cout << endl;
    vec.push_back(1);
    displayCapacity(vec);

    cout << endl;
    vec.push_back(2);
    displayCapacity(vec);

    cout << endl;
    vec.push_back(3);
    displayCapacity(vec);

    cout << endl;
    vec.push_back(4);
    displayCapacity(vec);

    cout << endl;
    vec.push_back(5);
    displayCapacity(vec);

    cout << endl;
    vec.push_back(6);
    displayCapacity(vec);

    cout << endl;
    for(auto &elem : vec)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

