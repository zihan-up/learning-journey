#include "widget.h"

#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QPushButton *btn1 = new QPushButton("按钮1");
    QPushButton *btn2 = new QPushButton("按钮2");
    QPushButton *btn3 = new QPushButton("按钮3");

    //布局管理器的使用步骤
    //1、创建布局管理器的对象
    //2、使用addWidget将各个需要布局的部件添加到布局管理器中
    //3、调用setLayout将布局管理器对象添加进来
    QVBoxLayout *vlayout = new QVBoxLayout;

    vlayout->addWidget(btn1);
    vlayout->addWidget(btn2);
    vlayout->addWidget(btn3);

    setLayout(vlayout);
}

Widget::~Widget()
{
}

