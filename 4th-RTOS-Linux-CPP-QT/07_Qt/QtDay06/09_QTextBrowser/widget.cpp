#include "widget.h"

#include <QTextBrowser>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);
    QTextBrowser *tb = new QTextBrowser(this);
    tb->move(100, 100);
    tb->resize(300, 300);

    tb->insertHtml("<a href='https://www.baidu.com'> 百度 </a>");
    tb->setOpenExternalLinks(true);//打开外部链接
}

Widget::~Widget()
{
}

