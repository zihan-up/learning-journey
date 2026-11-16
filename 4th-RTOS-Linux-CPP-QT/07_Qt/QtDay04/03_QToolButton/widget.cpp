#include "widget.h"

#include <QToolButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->move(100, 100);
    toolBtn->resize(300, 200);

    toolBtn->setIcon(QIcon(":/Image/linux.png"));
    toolBtn->setText("显示图标");
    toolBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

Widget::~Widget()
{
}

