#include "widget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        qDebug() << "鼠标左键被按压了";
    }

}

bool Widget::event(QEvent *ev)
{
    if(ev->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "鼠标按压事件在event中截胡----";
        return true;
    }

    return QWidget::event(ev);
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << "键盘上的按键按压了";
}

