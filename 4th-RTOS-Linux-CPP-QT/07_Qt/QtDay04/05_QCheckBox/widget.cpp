#include "widget.h"

#include <QCheckBox>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QCheckBox *box1 = new QCheckBox("味道鲜美",this);
    QCheckBox *box2 = new QCheckBox("环境干净",this);
    QCheckBox *box3 = new QCheckBox("都不行",this);

    box1->move(100, 100);
    box2->move(100, 200);
    box3->move(100, 300);

    //设置三态模式：选中、待选、未选中
    box1->setTristate(true);

    connect(box1, &QCheckBox::stateChanged, [](int stat){
        if(stat == Qt::Unchecked)
        {
            qDebug() << "未选中";
        }
        else if(stat == Qt::PartiallyChecked)
        {
            qDebug() << "待选中";
        }
        else
        {
            qDebug() << "选中";
        }

    });
}

Widget::~Widget()
{
}

