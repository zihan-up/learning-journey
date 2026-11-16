#include "widget.h"
#include <QComboBox>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{   
    resize(600, 480);
    QComboBox *cbox = new QComboBox(this);
    cbox->move(100, 100);
    cbox->resize(200, 40);

    cbox->addItem("北京市");
    cbox->addItem("天津市");
    cbox->addItem("上海市");
    cbox->addItem("重庆市");
    cbox->addItem("湖北省");
    cbox->addItem("湖南省");
    cbox->addItem("海南省");

    connect(cbox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int idx){
        qDebug() << "idx = " << idx;
        qDebug() << "文本信息: " << cbox->currentText();
    });
}

Widget::~Widget()
{
}

