#include "mainwindow.h"


#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("测试菜单栏中的工具栏");
    resize(600, 480);

    QToolBar *tbar = new QToolBar(this);
    tbar->resize(300, 50);
    QAction *newAc = tbar->addAction("新建");
    QAction *openAc = tbar->addAction("打开");
    QAction *saveAc = tbar->addAction("保存");
    saveAc->setIcon(QIcon(":/Image/rose.jpeg"));

    tbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    tbar->setFloatable(true);//设置是否可以漂浮
//    tbar->setMovable(false);//设置是否可以移动

}

MainWindow::~MainWindow()
{
}

