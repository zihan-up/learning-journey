#include "widget.h"

#include <QProgressBar>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QProgressBar *pb = new QProgressBar(this);
    pb->move(100, 100);
    pb->resize(300, 30);

    QPushButton *btn = new QPushButton("点击显示下载进度", this);
    btn->move(420, 100);
    btn->resize(180, 30);

    pb->setRange(0, 1000000);
    //设置进度调的显示格式
    //%p:按照百分制进行显示
    //%v:当前值
    //%m:总的值
    //pb->setFormat("%v/%m");

    connect(btn, &QPushButton::clicked, [=]{
        for(int idx = 0; idx <= 1000000; ++idx)
        {
            pb->setValue(idx);
        }
    });
}

Widget::~Widget()
{
}

