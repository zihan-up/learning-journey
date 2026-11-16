#include "widget.h"

#include <QTableView>
#include <QStandardItemModel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    //3、创建模型对象
    QStandardItemModel *model = new QStandardItemModel(this);

    //5、添加水平表头
    model->setHorizontalHeaderItem(0, new QStandardItem("学号"));
    model->setHorizontalHeaderItem(1, new QStandardItem("姓名"));
    model->setHorizontalHeaderItem(2, new QStandardItem("性别"));
    model->setHorizontalHeaderItem(3, new QStandardItem("分数"));

    //4、添加数据
    model->setItem(0, 0, new QStandardItem("191102"));
    model->setItem(0, 1, new QStandardItem("杨逍"));
    model->setItem(0, 2, new QStandardItem("男"));
    model->setItem(0, 3, new QStandardItem("680"));

    model->setItem(1, 0, new QStandardItem("191101"));
    model->setItem(1, 1, new QStandardItem("张三丰"));
    model->setItem(1, 2, new QStandardItem("男"));
    model->setItem(1, 3, new QStandardItem("700"));


    model->setItem(2, 0, new QStandardItem("191103"));
    model->setItem(2, 1, new QStandardItem("赵敏"));
    model->setItem(2, 2, new QStandardItem("女"));
    model->setItem(2, 3, new QStandardItem("748"));

    //1、创建视图对象
    QTableView *tabView = new QTableView(this);
    tabView->resize(800, 600);

    //2、调用setModel函数，指定模型
    tabView->setModel(model);

    tabView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->sort(0, Qt::DescendingOrder);
}

Widget::~Widget()
{
}

