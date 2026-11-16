#include "widget.h"
#include <QSpinBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);
    QSpinBox *spinBox = new QSpinBox(this);
    spinBox->move(100, 100);
    spinBox->resize(200, 30);

    //设置范围
    spinBox->setRange(-100, 100);
    //设置每次更改的步长
    spinBox->setSingleStep(10);
    //设置默认值
    spinBox->setValue(19);

}

Widget::~Widget()
{
}

