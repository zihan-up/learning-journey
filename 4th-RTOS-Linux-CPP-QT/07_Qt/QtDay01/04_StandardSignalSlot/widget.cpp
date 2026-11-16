#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

   // connect(ui->pushButton, &QPushButton::clicked, this, &Widget::close);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    qDebug() << "点击了按钮QPushButton，执行槽函数";
    qDebug("使用的是C的方式进行打印");
    close();
}
