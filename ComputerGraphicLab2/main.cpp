#include "bezclass.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BezClass *w = new BezClass;
    w->show();
    QObject::connect(w, SIGNAL(exit()),
                     &a, SLOT(quit()));

    return a.exec();
}
