#include "widget.h"

#include <QLCDNumber>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QLCDNumber *lcd = new QLCDNumber(this);
    lcd->move(100, 100);
    lcd->resize(200, 50);

    lcd->setDigitCount(7);
    //显示数据的函数display
    lcd->display(10.12345);
    lcd->setSegmentStyle(QLCDNumber::Flat);
}

Widget::~Widget()
{
}

