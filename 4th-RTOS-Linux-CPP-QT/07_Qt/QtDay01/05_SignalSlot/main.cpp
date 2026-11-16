#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;//w是栈对象
    w.show();
    return a.exec();
}
