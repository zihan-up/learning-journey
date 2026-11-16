#include "widget.h"

#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    //第一种：单行文本框
//    QLineEdit *lineEdit = new QLineEdit(this);
//    lineEdit->move(100, 50);
//    lineEdit->setText("你好");
//    //设置密码模式
//    lineEdit->setEchoMode(QLineEdit::Password);

    //第二种：纯文本框
//    QPlainTextEdit *ptEdit = new QPlainTextEdit(this);
//    ptEdit->move(100, 150);
//    ptEdit->setPlainText("对哈和大家还非得哈哈开发哈很发达哈哈发回复打开换肤大师");
//    ptEdit->insertPlainText("xxxhjdahdjahf");
//    ptEdit->setPlaceholderText("输入密码");//占位符文本

    //第三种：富文本框
    //在插入文本的时候，将QLineEdit以及QPlainTextEdit
    //中的所有插入文本的方式都进行了包含
    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->move(400, 150);
    textEdit->resize(500, 300);
//    textEdit->setText("heheh");
//    textEdit->setPlaceholderText("");
//    textEdit->setPlainText("xxx");
//    textEdit->insertPlainText("aaa");
    textEdit->insertPlainText("This is an Text Edit");

    //将光标获取出来，移动光标的位置，对选中的文字进行处理
    QTextCursor cursor = textEdit->textCursor();

    //移动光标的位置
    cursor.movePosition(QTextCursor::Start);
    //cursor.movePosition(QTextCursor::NextWord);
    //移动光标的位置，保持锚点
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);

    //设置选中字体的各种风格或者格式
    QTextCharFormat format;
    format.setFont(QFont("宋体"));
    format.setFontItalic(true);
    format.setFontPointSize(40);
    format.setForeground(QBrush(QColor(255, 0, 0)));

    cursor.mergeCharFormat(format);
}

Widget::~Widget()
{
}

