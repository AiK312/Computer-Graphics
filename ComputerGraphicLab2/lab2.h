#ifndef LAB2_H
#define LAB2_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QAction>
#include <QImage>
#include "math.h"
#include <QMap>
#include <time.h>


namespace Ui {
class Lab2;
}

class Lab2 : public QWidget
{
    Q_OBJECT

public:
    explicit Lab2(QWidget *parent = 0);
    ~Lab2();   

private slots:
    void on_pushButton_3_clicked();
    void on_buttonOpen_clicked();
    void on_buttonSave_clicked();
    void on_polylineButton_clicked();
    void on_antialiasingButton_clicked();

private:
    Ui::Lab2 *ui;
    QImage *image;
    QMap<int, int> *coordinateList;
};

#endif // LAB2_H
