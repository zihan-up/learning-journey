#include "widget.h"

#include <QLineEdit>
#include <QFormLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QLineEdit *lineEdit1 = new QLineEdit;
    QLineEdit *lineEdit2 = new QLineEdit;
    QLineEdit *lineEdit3 = new QLineEdit;

    QFormLayout *flayout = new QFormLayout;

    //flayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    flayout->addRow("学号", lineEdit1);
    flayout->addRow("姓名", lineEdit2);
    flayout->addRow("学校", lineEdit3);


    setLayout(flayout);
}

Widget::~Widget()
{
}

