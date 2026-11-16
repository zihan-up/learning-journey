#include "mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //set往往表明设置的是有一个，而add开头的函数表明可以设置多个
    setWindowTitle("测试主窗口中的菜单栏");
    //设置窗口的大小
    resize(600, 480);

    //创建菜单栏
    QMenuBar *mbar = new QMenuBar(this);
    mbar->resize(200, 100);
    //添加菜单项
    QMenu *fileMenu = mbar->addMenu("文件");
    QMenu *editMenu = mbar->addMenu("编辑");
    QMenu *saveMenu = mbar->addMenu("保存");

    //在文件菜单下，添加子菜单
    QMenu *newMenu = fileMenu->addMenu("新建");
    QMenu *openMenu = fileMenu->addMenu("打开");
    fileMenu->addSeparator();
    QMenu *closeMenu = fileMenu->addMenu("关闭");
    QAction *printAc = fileMenu->addAction("打印");

    QPushButton *btn = new QPushButton(this);
    btn->setText("按钮");
    btn->move(100, 50);
}

MainWindow::~MainWindow()
{
}

