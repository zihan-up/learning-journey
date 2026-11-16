#include "widget.h"

#include <QListView>
#include <QStringListModel>
#include <QStringList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    //4、创建真正存储数据的数据结构
    //本质其实就是QList<QString>
    QStringList slist;
    slist << "锄禾日当午" << "汗滴禾下土" << "谁知盘中餐" << "粒粒皆辛苦";

    //3、创建模型对象(存储数据)
    QStringListModel *model = new QStringListModel(slist, this);

    //1、创建视图对象(显示数据)
    QListView *lstView = new QListView(this);
    lstView->resize(600, 500);
    lstView->move(100, 100);

    //2、使用视图对象设置model
    lstView->setModel(model);
}

Widget::~Widget()
{
}

