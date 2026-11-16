#include "widget.h"

#include <QPainter>
#include <QPixmap>
#include <QPen>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //通过QPixmap类型创建的对象充当了绘图设备
    //对象一定要指定宽度与高度
    QPixmap pix(400, 300);
    pix.fill(Qt::white);

    //指定绘图设备
    QPainter pat(&pix);
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    pen.setWidth(3);
    pat.setPen(pen);

    pat.drawRect(10, 10, 200, 100);

    //保存绘制的图形存放的位置
    pix.save("F:/pix.jpg");
}

Widget::~Widget()
{
}

