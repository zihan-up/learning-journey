#include "HttpTestWidget.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttpTestWidget w;
    w.show();
    return a.exec();
}
