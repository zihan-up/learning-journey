#include "widget.h"

#include <QCommandLinkButton>
#include <QDesktopServices>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QCommandLinkButton *clb = new QCommandLinkButton(this);
    clb->move(100, 100);
    clb->resize(300, 200);

    clb->setText("1111");
    clb->setDescription("点击按钮可以跳转到百度");

    connect(clb, &QCommandLinkButton::clicked, []{
        QDesktopServices::openUrl(QUrl("www.baidu.com"));
    });

}

Widget::~Widget()
{
}

