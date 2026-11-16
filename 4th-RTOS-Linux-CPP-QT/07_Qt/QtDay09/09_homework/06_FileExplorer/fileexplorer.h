#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QApplication>
#include <QSplitter>
#include <QTreeWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileSystemModel>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

class FileExplorer : public QWidget
{
    Q_OBJECT
public:
    FileExplorer(QWidget *parent = nullptr);


private:
    void setWidgetLayout();
    void setupConnections();
    void setupContextMenu();


private slots:
    void showDirectoryContents(QTreeWidgetItem *item, int);
    void openFile(QTableWidgetItem *item);
    void showTreeContextMenu(const QPoint &pos);
    void showTableContextMenu(const QPoint &pos);
    void refreshTree();
    void openSelectedFile();
    void deleteSelectedFile();


private:
    QTreeWidget *dirTree;
    QTableWidget *fileTable;
    QMenu *treeMenu;
    QMenu *tableMenu;
};

#endif // FILEEXPLORER_H
