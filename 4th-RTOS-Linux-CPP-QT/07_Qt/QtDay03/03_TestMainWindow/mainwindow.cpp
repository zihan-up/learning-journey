#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QStatusBar>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("测试主窗口");
    resize(600, 480);

    //1、创建菜单栏
    QMenuBar *mbar = menuBar();
    //添加菜单栏到主窗口
    setMenuBar(mbar);

    //添加子菜单
    QMenu *fileMenu = mbar->addMenu("文件");
    QMenu *editMenu = mbar->addMenu("编辑");
    QMenu *toolMenu = mbar->addMenu("工具");

    //在文件子菜单中添加菜单项
    QAction *newAc = fileMenu->addAction("新建");
    QAction *openAc = fileMenu->addAction("打开");
    QAction *saveAc = fileMenu->addAction("保存");

    //2、创建工具栏
    //在QMainWindow中添加菜单栏、状态栏、工具栏等等，如果创建的
    //是堆对象，可以不用指定父对象
    QToolBar *tbar = new QToolBar(this);
    //将工具栏添加到主窗口中
    addToolBar(Qt::TopToolBarArea, tbar);//默认放在顶部
    tbar->setOrientation(Qt::Horizontal);

    //给工具栏添加菜单项
    tbar->addAction(newAc);
    tbar->addAction(openAc);
    tbar->addAction(saveAc);

    //设置停靠范围
    tbar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    //3、添加铆接部件（浮动窗口）
    QDockWidget *dockWid = new QDockWidget("浮动窗口", this);
    //将浮动窗口添加到主窗口中
    addDockWidget(Qt::TopDockWidgetArea, dockWid);
    //设置可以停靠的范围(要参考中心部件)
    dockWid->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    //4、设置中心部件
    QPushButton *btn = new QPushButton("按钮", this);
    setCentralWidget(btn);

    //5、状态栏
    QStatusBar *sbar = new QStatusBar(this);
    setStatusBar(sbar);

    QPushButton *btn1 = new QPushButton("按钮1", this);
    QPushButton *btn2 = new QPushButton("按钮2", this);
    QPushButton *btn3 = new QPushButton("按钮3", this);
    QPushButton *btn4 = new QPushButton("按钮4", this);
    sbar->addWidget(btn1);
    sbar->addWidget(btn2);
    sbar->addPermanentWidget(btn3);
    sbar->addPermanentWidget(btn4);
}

MainWindow::~MainWindow()
{
}

