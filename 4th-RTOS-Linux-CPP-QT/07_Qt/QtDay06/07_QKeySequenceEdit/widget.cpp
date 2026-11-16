#include "widget.h"

#include <QKeySequenceEdit>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QKeySequenceEdit *kse = new QKeySequenceEdit(this);
    kse->move(100, 100);
    kse->resize(200, 30);

    connect(kse, &QKeySequenceEdit::keySequenceChanged,
            [=](const QKeySequence &ks){
        if(ks == QKeySequence("Ctrl+Q"))
        {
            close();
        }
        else
        {
            qDebug() << "快捷方式制作失败";
        }

    });
}

Widget::~Widget()
{
}

