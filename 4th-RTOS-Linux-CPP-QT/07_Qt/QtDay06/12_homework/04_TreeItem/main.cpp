#include <QApplication>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //设置布局
    QWidget window;
    window.resize(600, 400);

    //QVBoxLayout *layout = new QVBoxLayout(&window);
    QVBoxLayout *layout = new QVBoxLayout;

    QTreeWidget treeWidget;
    QLabel pathLabel;
    pathLabel.setFrameShape(QFrame::Box);
    pathLabel.setFixedHeight(70);

    layout->addWidget(&treeWidget);
    layout->addWidget(&pathLabel);

    window.setLayout(layout);
    //布局设置结束

    //给treeWidget设置表头
    treeWidget.setHeaderLabels(QStringList() << "将帅名" << "将帅介绍");
    //设置树形部件项目
    QTreeWidgetItem *weaponryItem = new QTreeWidgetItem(QStringList() << "兵器");
    QTreeWidgetItem *fightItem = new QTreeWidgetItem(QStringList()<< "战斗力");
    QTreeWidgetItem *warRecordItem = new QTreeWidgetItem(QStringList() << "战绩");
    //加载顶层的节点
    treeWidget.addTopLevelItem(weaponryItem);
    treeWidget.addTopLevelItem(fightItem);
    treeWidget.addTopLevelItem(warRecordItem);

    //追加子结点
    QStringList heroL1;
    heroL1 << "关羽" << "关二爷，过五关斩六将";
    QTreeWidgetItem *l1 = new QTreeWidgetItem(heroL1);
    weaponryItem->addChild(l1);

    QStringList heroL2;
    heroL2 << "张飞" << "涿郡屠夫，长坂坡一声吼吓退曹操七十万大军";
    QTreeWidgetItem *l2 = new QTreeWidgetItem(heroL2);
    weaponryItem->addChild(l2);

    QStringList heroL3;
    heroL3 << "赵云" << "常山赵子龙，七进七出救阿斗";
    QTreeWidgetItem *l3 = new QTreeWidgetItem(heroL3);
    weaponryItem->addChild(l3);

    QStringList fight1;
    fight1 << "刀斧手" << "战斗力99";
    QTreeWidgetItem *f1 = new QTreeWidgetItem(fight1);
    fightItem->addChild(f1);

    QStringList fight2;
    fight2 << "嘴王" << "战斗力90";
    QTreeWidgetItem *f2 = new QTreeWidgetItem(fight2);
    fightItem->addChild(f2);

    QStringList fight3;
    fight3 << "侍卫" << "战斗力100";
    QTreeWidgetItem *f3 = new QTreeWidgetItem(fight3);
    fightItem->addChild(f3);

    QStringList record1;
    record1 << "站位" << "砍杀华雄";
    QTreeWidgetItem *r1 = new QTreeWidgetItem(record1);
    warRecordItem->addChild(r1);

    QStringList record2;
    record2 << "嘴位" << "死磕吕布";
    QTreeWidgetItem *r2 = new QTreeWidgetItem(record2);
    warRecordItem->addChild(r2);

    QStringList record3;
    record3 << "冲位" << "入曹营如探囊取物";
    QTreeWidgetItem *r3 = new QTreeWidgetItem(record3);
    warRecordItem->addChild(r3);


    QObject::connect(&treeWidget, &QTreeWidget::itemClicked, [&](QTreeWidgetItem *item) {
        QString path;


        //将item->text(1)添加到path的末尾
        path.append("/" + item->text(1));

        //头插遍历，直到将所有的值添加到前面，考查QString的函数prepend与append
        while (item != nullptr)
        {
            //prepend等价于是push_front
            path.prepend("/" + item->text(0));
            item = item->parent();
        }
        pathLabel.setText(path);
    });

    treeWidget.expandAll();

    window.show();
    return app.exec();
}
