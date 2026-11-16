#include "widget.h"

#include <QRadioButton>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QRadioButton *radio1 = new QRadioButton("男", this);
    QRadioButton *radio2 = new QRadioButton("女", this);
    radio1->move(100, 100);
    radio2->move(100, 150);

    //默认选中
    radio1->setChecked(true);

    connect(radio1, &QRadioButton::toggled, [=](bool stat){
        if(stat)
        {
            qDebug() << "男生被选中了";
        }
        else
        {
            qDebug() << "女生被选中了";
        }

        if(radio1->isChecked())
        {
            qDebug() << "也是男生选中了";
        }
    });
}

Widget::~Widget()
{
}

