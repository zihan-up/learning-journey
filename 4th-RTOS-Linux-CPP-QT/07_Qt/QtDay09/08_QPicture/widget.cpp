#include "widget.h"

#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建QPicture类型的对象
    QPicture pic;

    //指定绘图设备为QPicture对象pic
    QPainter pat(&pic);
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(3);
    pat.setPen(pen);

    //画矩形
    pat.drawRect(10, 10, 200, 100);

    pat.end();//结束绘图

    //保存绘制的图形存放的位置
    pic.save("F:/pic.pp");
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QPainter pat(this);

    QPicture pic;
    //加载图片
    pic.load("F:/pic.pp");

    pat.drawPicture(100, 100, pic);
}

