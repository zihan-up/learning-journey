#include "widget.h"
#include "mylabel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyLabel w;
    w.show();
    return a.exec();
}
