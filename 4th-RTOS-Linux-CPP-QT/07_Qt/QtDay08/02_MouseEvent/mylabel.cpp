#include "mylabel.h"

#include <QDebug>

MyLabel::MyLabel()
{
    resize(400, 300);
}

MyLabel::~MyLabel()
{

}

//鼠标进入
void MyLabel::enterEvent(QEvent *ev)
{
   qDebug() << ">>>鼠标进入范围了";
}

//鼠标离开
void MyLabel::leaveEvent(QEvent *ev)
{
    qDebug() << "鼠标离开范围了<<<";
}

//鼠标移动事件
void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{

}

//鼠标按压事件
void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << "鼠标--按压--事件触发了";
}
//鼠标释放事件
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << "鼠标--释放--事件触发了";
}
