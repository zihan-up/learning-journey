//自定义类对象的头文件
#include "mywidget.h"

//在Qt中，标准的类都是以字母Q开头的，任何一个类
//都会有与类名一样的头文件，所以在使用该类的时候
//需要将头文件引出来(特别注意：不需要像C++一样
//引出实体)

//Qt是基于C++开发的，所以C++中的语法在QT中是可以
//直接使用的
#include <QApplication>

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    //QApplication是应用程序类，a是该类创建的对象
    //注意：在一个Qt程序中QApplication只能创建
    //一个对象
    QApplication a(argc, argv);

    //MyWidget是自定义的类，该类继承了QWidget
    //w是MyWidget创建的对象
    MyWidget w;
    //show函数的作用就是将MyWidget对象显示出来（窗口显示出来）
    //默认情况下，如果不调用show，那么窗口是无法显示的
    w.show();
    //exec调用之后，会启动事件循环，目的就是等待事件的到来
    //事件到来之后，会存储到事件队列中
    //exec函数在调用quit函数或者exit函数的时候，会让循环结束
    return a.exec();

    //while(1){}
    //return 0;
}
