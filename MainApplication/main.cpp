#include "mainapplication.h"
#include "L1/lab1.h"
#include "L2/lab2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainApplication *w = new MainApplication();
    w->showMaximized();
    QObject::connect(w, SIGNAL(exit()),
                     &a, SLOT(quit()));

    return a.exec();
}
