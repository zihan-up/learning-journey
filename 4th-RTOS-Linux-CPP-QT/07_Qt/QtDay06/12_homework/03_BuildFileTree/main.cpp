#include <QApplication>
#include <QTreeWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QTreeWidget treeWidget;
    treeWidget.resize(600, 400);

    treeWidget.setHeaderLabels({"Name"});
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(&treeWidget, {"Root"});

    QTreeWidgetItem *folder1 = new QTreeWidgetItem(rootItem, {"Folder 1"});
    new QTreeWidgetItem(folder1, {"File 1.1"});
    new QTreeWidgetItem(folder1, {"File 1.2"});

    QTreeWidgetItem *folder2 = new QTreeWidgetItem(rootItem, {"Folder 2"});
    new QTreeWidgetItem(folder2, {"File 2.1"});

    treeWidget.expandAll();
    treeWidget.show();

    return app.exec();
}
