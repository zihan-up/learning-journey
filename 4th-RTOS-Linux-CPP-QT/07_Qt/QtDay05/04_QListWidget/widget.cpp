#include "widget.h"

#include <QListWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    QListWidget *lstWid = new QListWidget(this);
    lstWid->move(100, 100);
    lstWid->resize(800, 600);

    //第一种添加的方式，以字符串的形式进行添加
    lstWid->addItem("锄禾日当午");
    lstWid->addItem("汗滴禾下土");

    //第二种添加的方式，构建QListWidgetItem对象(可以更改文本的显示方式)
    QListWidgetItem *item1 = new QListWidgetItem("白日依山尽");
    item1->setTextAlignment(Qt::AlignRight);
    lstWid->addItem(item1);
    QListWidgetItem *item2 = new QListWidgetItem("黄河入海流");
    item2->setTextAlignment(Qt::AlignHCenter);
    lstWid->addItem(item2);

    //第三种添加的方式，以QStringList类型的形式进行添加
    lstWid->addItems(QStringList() << "锄禾日当午" << "汗滴禾下土");
}

Widget::~Widget()
{
}

