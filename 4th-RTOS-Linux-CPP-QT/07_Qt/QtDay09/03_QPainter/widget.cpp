#include "widget.h"

#include <QPainter>
#include <QPen>
#include <QBrush>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *ev)
{
    //创建绘制器的对象
    QPainter pat(this);

    //创建画笔对象
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(5);
    pat.setPen(pen);

    //创建画刷对象
    QBrush brush;
    brush.setStyle(Qt::CrossPattern);
    brush.setColor(Qt::cyan);
    pat.setBrush(brush);

    //开始绘图
    //画直线
    pat.drawLine(50, 50, 200, 200);
    //画矩形
    pat.drawRect(200, 50, 200, 100);
    //画圆形
    pat.drawEllipse(50, 200, 100, 100);
    //画椭圆
    pat.drawEllipse(200, 200, 200, 100);
    pat.drawText(400, 100, "好好学习，天天向上");
}

