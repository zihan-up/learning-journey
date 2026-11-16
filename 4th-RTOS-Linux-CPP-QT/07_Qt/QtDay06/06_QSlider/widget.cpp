#include "widget.h"

#include <QSlider>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QSlider *hslider = new QSlider(Qt::Horizontal, this);
    hslider->move(100, 100);
    hslider->resize(200, 20);
    //设置范围
    hslider->setRange(0, 100);
    //设置刻度
    hslider->setTickInterval(10);
    //设置刻度与滑动条的方位
    hslider->setTickPosition(QSlider::TicksAbove);

    QSlider *vslider = new QSlider(Qt::Vertical, this);
    vslider->resize(20, 200);
}

Widget::~Widget()
{
}

