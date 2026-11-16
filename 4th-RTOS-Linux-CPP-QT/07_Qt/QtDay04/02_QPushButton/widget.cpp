#include "widget.h"

#include <QPushButton>
#include <QDebug>
#include <QMenu>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("测试普通按钮");

    //重置窗口大小
    resize(600, 480);

    //指定父对象的方式有两种
    //（1）构造函数中传参
    //(2)调用setParent
    QPushButton *btn = new QPushButton;
    btn->setParent(this);

    //移动按钮
    btn->move(100, 100);
    //设置按钮的大小
    btn->resize(300, 200);
    //设置按钮的文本
    btn->setText("测试按钮");
    //这两行代码可以去掉QString中的双引号
    qDebug().noquote() << "=====" << btn->text();
    qDebug() << "=====" << btn->text().toUtf8().constData();

    btn->setFlat(true);//设置扁平

    //按钮中是可以添加菜单的
    QMenu *me = new QMenu("文件", this);
    me->addMenu("新建");
    btn->setMenu(me);
}

Widget::~Widget()
{
}

