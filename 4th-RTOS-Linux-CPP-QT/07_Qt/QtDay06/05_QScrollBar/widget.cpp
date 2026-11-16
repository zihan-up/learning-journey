#include "widget.h"

#include <QScrollBar>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QScrollBar *hsb = new QScrollBar(Qt::Horizontal, this);
    hsb->move(100, 100);
    hsb->resize(400, 30);


    QScrollBar *vsb = new QScrollBar(Qt::Vertical, this);
    vsb->resize(30, 400);
}

Widget::~Widget()
{
}

