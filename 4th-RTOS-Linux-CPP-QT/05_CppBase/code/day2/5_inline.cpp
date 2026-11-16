#include <iostream>
using std::cout;
using std::endl;
//#define MAX(a, b) (a) > (b) ? (a) : (b) 
#define MAX(a, b) ((a) > (b) ? (a) : (b))

inline
int max(int x, int y){
    return x > y ? x : y;
}

void test(){
    int result = MAX(20,10) + 20;//result的值是多少？
    
    int result2 = MAX(10,20) + 20;//result2的值是多少？
    cout << result << ":" << result2 << endl;

    int result3 = max(10, 20) + 20;
    int result4 = max(20, 10) + 20;
    cout << result3 << ":" << result4 << endl;
}

void test2(){
    int i = 4,j = 3;
    int result = MAX(i++,j);
    cout << result << endl; //result = 5；
    cout << i << endl; //i = 6;
}
void test3(){
    int i = 4,j = 3;
    int result = max(i++,j);
    cout << result << endl; //result = 4；
    cout << i << endl; //i = 5;
}

int main()
{
    test3();
    return 0;
}

