#include "lab1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lab1 w;
    w.show();

    return a.exec();
}
