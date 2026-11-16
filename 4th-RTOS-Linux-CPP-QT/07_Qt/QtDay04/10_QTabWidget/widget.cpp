#include "widget.h"

#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QTabWidget *tabWid = new QTabWidget(this);
    tabWid->move(100, 100);
    tabWid->resize(400, 300);

    QWidget *w1 = new QWidget(this);
    QWidget *w2 = new QWidget(this);

    tabWid->addTab(w1, "张三");
    tabWid->addTab(w2, "李四");

    QLabel *label = new QLabel("选择");
    QLineEdit *lineEdit = new QLineEdit;
    QPushButton *btn = new QPushButton("点击按钮");

    QHBoxLayout *hlayout = new QHBoxLayout;

    hlayout->addWidget(label);
    hlayout->addWidget(lineEdit);
    hlayout->addWidget(btn);

    w1->setLayout(hlayout);

    tabWid->setMovable(true);
    tabWid->setTabsClosable(true);
    tabWid->setTabShape(QTabWidget::Triangular);
    tabWid->setTabPosition(QTabWidget::South);

    connect(btn, &QPushButton::clicked, [=]{
        qDebug() << "打印单行文本框中的内容 :" << lineEdit->text();
    });

    connect(tabWid, &QTabWidget::tabCloseRequested, [=](int idx){
        qDebug() << "idx = " << idx;
        tabWid->removeTab(idx);
    });
}

Widget::~Widget()
{
}

