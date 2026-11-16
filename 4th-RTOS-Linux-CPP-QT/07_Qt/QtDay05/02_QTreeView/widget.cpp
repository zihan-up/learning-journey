#include "widget.h"

#include <QTreeView>
#include <QStandardItemModel>
#include <QList>
#include <QStandardItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(1000, 800);

    //3、创建模型对象
    QStandardItemModel *model = new QStandardItemModel(this);

    //7、设置水平标签
    model->setHorizontalHeaderLabels(QStringList() << "编号"
                                     << "初中部 | 高中部");

    //--------顶层节点------------
    //5、使用QList数据类型存储QStandardItem *的指针
    QList<QStandardItem *> root;
    //6、每一个数据其实都是一个个的QStandardItem类型的对象
    QStandardItem *one = new QStandardItem("1");
    QStandardItem *mid = new QStandardItem("初中部");

    root.push_back(one);
    root.push_back(mid);

    //4、使用model对象调用相应的函数appendRow添加数据
    model->appendRow(root);

    //----------第二层节点---------
    QList<QStandardItem *> child1;
    QStandardItem *oneone = new QStandardItem("11");
    QStandardItem *yinianji = new QStandardItem("一年级");

    child1.push_back(oneone);
    child1.push_back(yinianji);

    one->appendRow(child1);

    //----------第三层节点---------
    QList<QStandardItem *> son1;
    QStandardItem *oneoneone = new QStandardItem("111");
    QStandardItem *yiban = new QStandardItem("一班");

    son1.push_back(oneoneone);
    son1.push_back(yiban);

    oneone->appendRow(son1);

    //----------第三层节点的兄弟节点---------
    QList<QStandardItem *> son2;
    QStandardItem *oneonetwo = new QStandardItem("112");
    QStandardItem *erban = new QStandardItem("二班");

    son2.push_back(oneonetwo);
    son2.push_back(erban);

    oneone->appendRow(son2);

    //--------顶层节点的兄弟节点-----------
    QList<QStandardItem *> root2;
    QStandardItem *two = new QStandardItem("2");
    QStandardItem *high = new QStandardItem("高中部");

    root2.push_back(two);
    root2.push_back(high);

    model->appendRow(root2);

    //1、创建树视图对象
    QTreeView *treeView = new QTreeView(this);
    treeView->resize(800, 600);

    //2、调用setMode函数，指定模型对象
    treeView->setModel(model);

    //使用该函数，将数据全部展开
    treeView->expandAll();
}

Widget::~Widget()
{
}

