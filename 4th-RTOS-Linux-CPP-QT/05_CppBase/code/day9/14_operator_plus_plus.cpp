#include <iostream>
using std::cout;
using std::endl;
//复数：相加其实就是实部 + 实部，虚部 + 虚部
class Complex{
public:
    Complex(int real, int image)
    :_real(real)
    ,_image(image)
    {

    }


    void print(){
        cout << "_real=" << _real << ",_image=" << _image << endl;
    }

    //对于+=运算符进行重载
    Complex & operator+=(const Complex & c2){
        _real += c2._real;
        _image += c2._image;
        return *this;
    }

    //前置++操作
    //返回的是谁？自己
    Complex & operator++(){
        cout << "前置++"  << endl;
        ++_real;
        ++_image;
        return *this;
    }

    //后置++操作
    //返回的是什么？拷贝的对象
    Complex operator++(int){
        cout << "后置++ " << endl;
        //利用拷贝构造函数创建一个临时对象
        Complex temp(*this);
        ++_real;
        ++_image;
        return temp;
    }

    //for(int i = 0; i < 10; ++i)尽量去写前置++

private:
    //实部
    int _real;
    //虚部
    int _image;
};
//对于内置数据类型来说，前置++和后置++的区别在哪？？？？？
//int a= 10;
//++a;先自增，后返回
//a++;先返回，后自增，会有一个拷贝的过程
void test2(){
    Complex c1(1, 2);
    c1++;
    cout << "==============" << endl;
    Complex c2(3, 4);
    ++c2;
}
void test(){
    Complex c1(1, 2), c2(3, 4);
    //编译器会将下面的代码解析成c1.operator+=(c2);
    c1 += c2;
    c1.print();
}

//再来看一个案例：求解点的坐标相加操作

int main()
{
    test2();
    return 0;
}

