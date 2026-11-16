#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(600, 400);

    //QVBoxLayout *layout = new QVBoxLayout(&window);
    QVBoxLayout *layout = new QVBoxLayout;

    QListWidget *listWidget = new QListWidget;
    QPushButton *addButton = new QPushButton("Add Item");
    QPushButton *removeButton = new QPushButton("Remove Selected");

    layout->addWidget(listWidget);
    layout->addWidget(addButton);
    layout->addWidget(removeButton);

    window.setLayout(layout);

    int itemCounter = 1;

    QObject::connect(addButton, &QPushButton::clicked, [&]{
        listWidget->addItem("Item " + QString::number(itemCounter++));
    });

    QObject::connect(removeButton, &QPushButton::clicked, [&] {
        delete listWidget->takeItem(listWidget->currentRow());
    });

    window.show();

    return app.exec();
}
