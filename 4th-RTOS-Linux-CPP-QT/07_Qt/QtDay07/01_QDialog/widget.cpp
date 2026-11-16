#include "widget.h"

#include <QDialog>
#include <QPushButton>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 480);

    QPushButton *btn1 = new QPushButton("创建模态对话框", this);
    QPushButton *btn2 = new QPushButton("创建非模态对话框,栈对象", this);
    QPushButton *btn3 = new QPushButton("创建非模态对话框,堆对象", this);
    btn1->move(100, 50);
    btn2->move(100, 150);
    btn3->move(100, 250);

    btn1->resize(300, 50);
    btn2->resize(300, 50);
    btn3->resize(300, 50);

    connect(btn1, &QPushButton::clicked, []{
        QDialog dlg;
        dlg.exec();//创建了模态对话框，阻止与其他窗口之间的交互
        qDebug() << "创建了模态对话框";
    });

    connect(btn2, &QPushButton::clicked, []{
        QDialog dlg;//栈对象
        dlg.show();//创建了非模态对话框，但是因为dlg是局部对象，用完
                   //之后会立马销毁，同时show函数不会阻塞，调用完成
                   //完成之后会立马返回

        qDebug() << "创建了非模态对话框,栈对象";
    });

    connect(btn3, &QPushButton::clicked, [=]{
        QDialog *pdlg = new QDialog;//堆对象
        pdlg->show();//因为对话框创建的是堆对象，所以生命周期是
                     //比lambda表达式要长，这样就可以在调用本函数
                     //的时候，会持久显示

       //可以在窗口关闭的时候，将申请的堆空间回收掉
       //(本函数加上枚举值，可以解决内存泄漏的风险)
       pdlg->setAttribute(Qt::WA_DeleteOnClose);

        qDebug() << "创建了非模态对话框,堆对象";
    });
}

Widget::~Widget()
{
}

