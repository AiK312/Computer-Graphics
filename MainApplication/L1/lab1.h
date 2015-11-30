#ifndef LAB1_H
#define LAB1_H

#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <math.h>
#include <QAction>

namespace Ui {
class Lab1;
}

class Lab1 : public QDialog
{
    Q_OBJECT

public:
    explicit Lab1(QWidget *parent = 0);
    Lab1(QWidget *parent, QImage &imageFromMain);
    ~Lab1();

private slots:
    void on_buttonLine_clicked();
    void on_buttonRing_clicked();
    void on_buttonElipse_clicked();

signals:
    void exit();
    void endFunc();

private:
    Ui::Lab1 *ui;
    QImage* image;
};

#endif // LAB1_H
