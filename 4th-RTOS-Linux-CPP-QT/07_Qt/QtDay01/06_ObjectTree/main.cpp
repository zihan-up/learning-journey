#include "widget.h"
#include "myobject.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    MyObject obj;//栈对象
    MyObject *pobj = new MyObject(&w);//堆对象
    MyObject *pobj2 = new MyObject(&obj);//堆对象

    //delete pobj;//使用的是C++中的new与delete的语法
    //作用与delete是一样的,这是Qt自己提供对堆空间回收的方式
    //pobj->deleteLater();

    return a.exec();
}
