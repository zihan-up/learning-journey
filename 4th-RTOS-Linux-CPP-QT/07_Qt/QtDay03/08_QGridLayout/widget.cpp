#include "widget.h"

#include <QPushButton>
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QPushButton *btn1 = new QPushButton("第一个按钮");
    QPushButton *btn2 = new QPushButton("第二个按钮");
    QPushButton *btn3 = new QPushButton("第三个按钮");
    QPushButton *btn4 = new QPushButton("第四个按钮");

    //给btn1设置了大小策略（水平策略，垂直策略）
    btn1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QGridLayout *glayout = new QGridLayout;

    //(部件，起始行，起始列，占据的行数，占据的列数);
    //如果没有指定占据的行数与列数，那么默认占据一行一列
    glayout->addWidget(btn1, 0, 0, 3, 1);
    glayout->addWidget(btn2, 0, 2);
    glayout->addWidget(btn3, 2, 1, 1, 2);
    glayout->addWidget(btn4, 1, 3);

    setLayout(glayout);
}

Widget::~Widget()
{
}

