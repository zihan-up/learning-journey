#include "widget.h"

#include <QPushButton>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);
#if 0
    QPushButton *btn1 = new QPushButton("按钮1", this);
    QPushButton *btn2 = new QPushButton("按钮2", this);
    QPushButton *btn3 = new QPushButton("按钮3", this);
    btn2->move(200, 0);
    btn3->move(400, 0);
#endif

    QPushButton *btn1 = new QPushButton("按钮1");
    QPushButton *btn2 = new QPushButton("按钮2");
    QPushButton *btn3 = new QPushButton("按钮3");

    //布局管理器的使用步骤
    //1、创建布局管理器的对象
    //2、使用addWidget将各个需要布局的对象添加到布局管理器中
    //3、调用setLayout将布局管理器对象添加进来
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(btn1);
    hlayout->addWidget(btn2);
    hlayout->addWidget(btn3);

    setLayout(hlayout);
}

Widget::~Widget()
{
}


