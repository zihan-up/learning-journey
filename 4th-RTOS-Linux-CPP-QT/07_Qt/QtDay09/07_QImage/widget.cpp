#include "widget.h"

#include <QPainter>
#include <QImage>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent *ev)
{
    QImage img;
    img.load(":/butterfly.png");


    QPainter pat(this);

    for(int i = 100; i < 300; ++i)
    {
        for(int j = 100; j < 300; ++j)
        {
            QRgb t = qRgb(255, 0, 0);
            //像素处理的函数
            img.setPixel(i, j, t);
        }
    }

    pat.drawImage(0, 0, img);
}

