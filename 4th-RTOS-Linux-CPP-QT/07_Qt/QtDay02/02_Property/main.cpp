#include "widget.h"
#include "myobject.h"

#include <QApplication>
#include <QDebug>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaMethod>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    MyObject *pobj = new MyObject(&w);//w是堆对象的父对象,使用了对象树

    //使用属性声明方式中的函数设置与获取属性
    pobj->setName("hello");
    qDebug() << "属性值name = " << pobj->getName();

    //连接信号与槽
    QObject::connect(pobj, &MyObject::nameChanged, [](const QString &nm){
        qDebug() << "lambda中的信号传递过来的值 " << nm;
    });

    //还可以使用动态属性的方式设置在头文件中显示定义的属性name
    pobj->setProperty("name", "wangdao");
    qDebug() << "属性值name = " << pobj->getName();
    qDebug() << "属性值name = " << pobj->property("name").toString();

    //调用头文件中的属性中的函数setName修改了属性的值，所以触发了信号nameChanged
    pobj->setName("hello");
    qDebug() << "属性值name222 = " << pobj->getName();
    qDebug() << "属性值name222 = " << pobj->property("name").toString();


    //----------------------测试运行时类型信息-----------
    qDebug() << endl << endl << endl;
    MyObject obj;//obj就是QObject的派生类MyObject的对象

    //如何获取obj的类型名字、属性、方法
    const QMetaObject *pmetaObj = obj.metaObject();

    qDebug() << "obj对象类的名字" << pmetaObj->className();

    qDebug() << endl ;
    //通过元对象获取基对象obj中的属性
    for(int idx = 0; idx < pmetaObj->propertyCount(); ++idx)
    {
        QMetaProperty pro = pmetaObj->property(idx);
        qDebug() << "属性的名字：" << pro.name()
                 << "属性的类型: " << pro.typeName();
    }

    qDebug() << endl ;
    //通过元对象获取基对象obj中的方法
    for(int idx = 0; idx < pmetaObj->methodCount(); ++idx)
    {
        QMetaMethod mthd = pmetaObj->method(idx);
        qDebug() << "方法的名字 " << mthd.methodSignature();
    }

    return a.exec();
}
