#include "fileexplorer.h"

#include <QApplication>
#include <QSplitter>
#include <QTreeWidget>

FileExplorer::FileExplorer(QWidget *parent )
    : QWidget(parent)
{
    setWindowTitle("文件浏览器");
    resize(800, 600);

    setWidgetLayout();
    setupConnections();
    setupContextMenu();
}

void FileExplorer::setWidgetLayout()
{
    //创建一个可调整大小的分割窗口组件
    QSplitter *splitter = new QSplitter(this);

    // 左侧目录树
    dirTree = new QTreeWidget;
    dirTree->setHeaderLabel("目录");
    dirTree->setColumnCount(1);
    dirTree->setContextMenuPolicy(Qt::CustomContextMenu);

    // 右侧文件表
    fileTable = new QTableWidget;
    //设置表格的列数为 3
    fileTable->setColumnCount(3);
    fileTable->setHorizontalHeaderLabels({"文件名", "大小", "修改日期"});
    //让最后一列（“修改日期”）自动拉伸填充剩余空间。
    fileTable->horizontalHeader()->setStretchLastSection(true);
    //允许为表格 自定义右键菜单（如“打开”“删除”“重命名”等操作)
    fileTable->setContextMenuPolicy(Qt::CustomContextMenu);
    //设置选中模式为 整行选中（而非单个单元格）
    fileTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    splitter->addWidget(dirTree);
    splitter->addWidget(fileTable);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);

    // 初始化目录树
    QTreeWidgetItem *root = new QTreeWidgetItem(dirTree, {"我的电脑"});
    QTreeWidgetItem *documents = new QTreeWidgetItem(root, {"文档"});
    QTreeWidgetItem *desktop = new QTreeWidgetItem(root, {"桌面"});
    QTreeWidgetItem *downloads = new QTreeWidgetItem(root, {"下载"});

    // 展开根节点
    dirTree->expandItem(root);
}

void FileExplorer::setupConnections()
{
    connect(dirTree, &QTreeWidget::itemClicked, this, &FileExplorer::showDirectoryContents);
    connect(fileTable, &QTableWidget::itemDoubleClicked, this, &FileExplorer::openFile);
    connect(dirTree, &QTreeWidget::customContextMenuRequested,
            this, &FileExplorer::showTreeContextMenu);
    connect(fileTable, &QTableWidget::customContextMenuRequested,
            this, &FileExplorer::showTableContextMenu);
}

void FileExplorer::setupContextMenu()
{
    treeMenu = new QMenu(this);
    QAction *refreshAction = new QAction("刷新", this);
    //将动作添加到菜单
    treeMenu->addAction(refreshAction);
    //点击“刷新”时调用函数
    connect(refreshAction, &QAction::triggered, this, &FileExplorer::refreshTree);

    tableMenu = new QMenu(this);
    //创建“打开”或者"删除"动作
    QAction *openAction = new QAction("打开", this);
    QAction *deleteAction = new QAction("删除", this);
    tableMenu->addAction(openAction);
    tableMenu->addAction(deleteAction);
    //连接"打开"信号槽,打开选中的文集N
    connect(openAction, &QAction::triggered, this, &FileExplorer::openSelectedFile);
    //连接"删除"信号槽,删除选中的文件
    connect(deleteAction, &QAction::triggered, this, &FileExplorer::deleteSelectedFile);
}

void FileExplorer::showDirectoryContents(QTreeWidgetItem *item, int)
{
    // 模拟显示目录内容
    fileTable->setRowCount(0);

    QStringList mockFiles;
    if (item->text(0) == "文档")
    {
        mockFiles << "简历.doc" << "报告.pdf" << "笔记.txt";

    }
    else if (item->text(0) == "桌面")
    {
        mockFiles << "快捷方式.lnk" << "图片.png" << "项目文件.pro";
    }
    else if (item->text(0) == "下载")
    {
        mockFiles << "安装包.exe" << "电影.mp4" <<"音乐.mp3";
    }
    else
    {
        return;
    }

    //foreach (const QString &fileName, mockFiles)
    for (const QString &fileName : mockFiles)
    {
        //获取当前表格行数
        int row = fileTable->rowCount();
        //在尾部插入行
        fileTable->insertRow(row);
        //在第0列设置文件名
        fileTable->setItem(row, 0, new QTableWidgetItem(fileName));
        //在第一列设置文件大小
        fileTable->setItem(row, 1, new QTableWidgetItem("100 KB"));
        //在第二列设置修改日期
        fileTable->setItem(row, 2, new QTableWidgetItem("2023-01-01"));
    }
}


void FileExplorer::openFile(QTableWidgetItem *item)
{
    QMessageBox::information(this, "文件打开", "尝试打开: " + item->text());
}

//在目录树上显示右键上下文菜单（即之前定义的 treeMenu，包含“刷新”选项）。
void FileExplorer::showTreeContextMenu(const QPoint &pos)
{
    treeMenu->exec(dirTree->mapToGlobal(pos));
}
//在文件列表上显示右键上下文菜单（tableMenu，包含“打开”和“删除”选项）。
void FileExplorer::showTableContextMenu(const QPoint &pos)
{
    tableMenu->exec(fileTable->mapToGlobal(pos));
}

void FileExplorer::refreshTree()
{
    QMessageBox::information(this, "刷新", "目录树已刷新");
}

//当用户点击文件列表的 “打开” 菜单项时，尝试打开当前选中的文件
void FileExplorer::openSelectedFile()
{
    //获取当前选中的表格项
    if (fileTable->currentItem())
        openFile(fileTable->currentItem());
}

//当用户点击文件列表的 “删除” 菜单项时，删除当前选中的文件行
void FileExplorer::deleteSelectedFile()
{
    if (fileTable->currentItem())
    {
        //获取当前选中行的索引
        int row = fileTable->currentRow();
        //获取当前选中行的索引
        fileTable->removeRow(row);
    }
}
