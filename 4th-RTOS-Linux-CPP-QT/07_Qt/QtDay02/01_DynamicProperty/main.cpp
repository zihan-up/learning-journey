#include "widget.h"
#include "myobject.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    MyObject *pobj = new MyObject(&w);

    //设置属性
    pobj->setProperty("name", "wangdao");
    //获取对应属性name的值
    qDebug() << "属性name = " << pobj->property("name").toString();

    //设置属性，比如：年龄
    pobj->setProperty("age", 20);
    //获取对应属性name的值
    qDebug() << "属性age = " << pobj->property("age").toInt();

    return a.exec();
}
