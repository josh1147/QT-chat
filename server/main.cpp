#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w1("1"),w2("2"),w3("3"),w4("4");

    w1.show();
    w2.show();
    w3.show();
    w4.show();
    return a.exec();
}
