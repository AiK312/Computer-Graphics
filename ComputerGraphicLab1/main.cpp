#include "lab1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lab1 *w = new Lab1;
    w->show();

    QObject::connect(w, SIGNAL(exit()),
                     &a, SLOT(quit()));

    return a.exec();
}
