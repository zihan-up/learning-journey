#include <iostream>
using std::cout;
using std::endl;


void bool_func(bool b){
    if(b){
        cout <<"true" << endl;
    }else {
        cout <<"false" << endl;
    }
}

void test(){
    bool b1 = -100;
    bool b2 = 100;
    bool b3 = 0;
    bool b4 = 1;
    bool b5 = true;
    bool b6 = false;
    bool_func(b1);
    bool_func(b2);
    bool_func(b3);
    bool_func(b4);
    bool_func(b5);
    bool_func(b6);
}

int main()
{
    test();
    return 0;
}

