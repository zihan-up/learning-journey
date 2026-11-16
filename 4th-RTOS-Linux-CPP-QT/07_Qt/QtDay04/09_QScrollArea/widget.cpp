#include "widget.h"

#include <QScrollArea>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);
    QScrollArea *sa = new QScrollArea(this);
    sa->resize(600, 400);

    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap(":/wangdao.png"));
    sa->setWidget(label);
}

Widget::~Widget()
{
}

