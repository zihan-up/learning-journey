#include "widget.h"
#include <QPushButton>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QDebug>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    QPushButton *btn1 = new QPushButton("测试消息对话框", this);
    QPushButton *btn2 = new QPushButton("测试颜色对话框", this);
    QPushButton *btn3 = new QPushButton("测试字体对话框", this);
    QPushButton *btn4 = new QPushButton("测试文件对话框", this);

    QPlainTextEdit *pte = new QPlainTextEdit(this);

    btn1->move(100, 50);
    btn2->move(100, 150);
    btn3->move(100, 250);
    btn4->move(100, 350);
    pte->move(420, 50);

    btn1->resize(300, 50);
    btn2->resize(300, 50);
    btn3->resize(300, 50);
    btn4->resize(300, 50);
    pte->resize(500, 600);

    //测试消息对话框
    connect(btn1, &QPushButton::clicked, [=]{
       // QMessageBox::critical(this, "critical", "严重错误");
       // QMessageBox::information(this, "information", "提示信息");
       // QMessageBox::question(this, "question", "问题信息");
        QMessageBox::warning(this, "warning", "警告信息");
    });

    //测试颜色对话框
    connect(btn2, &QPushButton::clicked, [=]{
       QColor col = QColorDialog::getColor();
       qDebug() << "红色值：" << col.red()
                << "蓝色值: " << col.blue()
                << "绿色值: " << col.green();
    });

    //测试字体对话框
    connect(btn3, &QPushButton::clicked, [=]{
        bool ok;
        QFont font = QFontDialog::getFont(&ok, QFont("宋体"), this, "字体对话框");
        qDebug() <<"ok = " << ok
                 << "字体:" << font.family()
                 << "字体大小:" << font.pointSize()
                 << "是否斜体:" << font.italic()
                 << "是否加粗:"  << font.bold();
    });

    //测试文件对话框(重要)
    connect(btn4, &QPushButton::clicked, [=]{
        QString path =
                QFileDialog::getOpenFileName(this, "caption"
                                             , "C:/Users/lili/Desktop/嵌入式4期/2Qt课件"
                                             //如果需要过滤，可以使用;;
                                             , "(*.pptx);;(*.pdf);;(*.txt)");
        qDebug() <<"path = " << path;

        //----读文本文件----
        QFile fl(path);
        fl.open(QIODevice::ReadOnly);//只读方式打开
        //QByteArray字节数组
        QByteArray ba = fl.readAll();

        QString msg(ba);

        pte->clear();
        pte->insertPlainText(msg);

        fl.close();
    });
}

Widget::~Widget()
{
}

