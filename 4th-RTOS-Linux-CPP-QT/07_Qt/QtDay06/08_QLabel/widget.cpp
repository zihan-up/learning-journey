#include "widget.h"

#include <QLabel>
#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    QLabel *label = new QLabel(this);
    label->resize(1000, 800);

    //第一种：设置文本
    label->setText("标签");
    //设置外框的形状
    label->setFrameShape(QFrame::Box);

    //第二种：设置静态图片
    //label->setPixmap(QPixmap(":/Image/butterfly.png"));


    //第三种：设置动图
    QMovie *me = new QMovie(":/Image/duck.gif");
    label->setMovie(me);
    me->start();
}

Widget::~Widget()
{
}

