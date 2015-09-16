#ifndef BEZCLASS_H
#define BEZCLASS_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QImage>
#include "math.h"

namespace Ui {
class BezClass;
}

class BezClass : public QMainWindow
{
    Q_OBJECT

public:
    explicit BezClass(QWidget *parent = 0);
    ~BezClass();

private:
    Ui::BezClass *ui;
    QAction* actionOpen;
    QAction* actionSave;
    QImage* image;

private slots:
    void menuExit();
    void menuOpenFile();
    void menuSaveFile();


    void on_pushButton_clicked();

signals:
    void exit();

};

#endif // BEZCLASS_H
