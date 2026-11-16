#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> c = {1, 2, 3};
    cout << "The vector holds: ";
    for(auto& el: c) 
        cout << el << ' ';
    cout << endl;
    cout << "size() = " << c.size() << endl;
    cout << "capacity() = " << c.capacity() << endl;

    cout << endl << endl;
    c.resize(100);
    cout << "After resize up to 5: ";
    for(auto& el: c) 
        cout << el << ' ';
    cout << endl;
    cout << "size() = " << c.size() << endl;
    cout << "capacity() = " << c.capacity() << endl;

    cout << endl << endl;
    c.resize(2);
    cout << "After resize down to 2: ";
    for(auto& el: c) 
        cout << el << ' ';
    cout << endl;
    cout << "size() = " << c.size() << endl;
    cout << "capacity() = " << c.capacity() << endl;
}
