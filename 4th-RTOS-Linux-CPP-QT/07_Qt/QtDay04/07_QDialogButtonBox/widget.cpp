#include "widget.h"

#include <QDialogButtonBox>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QDialogButtonBox *dbb = new QDialogButtonBox(this);
    dbb->move(100, 100);
    dbb->resize(400, 300);

    dbb->addButton(QDialogButtonBox::Ok);
    dbb->addButton(QDialogButtonBox::Cancel);

    QPushButton *btn = new QPushButton("自定义按钮", this);
    dbb->addButton(btn, QDialogButtonBox::AcceptRole);

}

Widget::~Widget()
{
}

