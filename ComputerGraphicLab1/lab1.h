#ifndef LAB1_H
#define LAB1_H

#include <QWidget>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <math.h>
#include <QAction>

namespace Ui {
class Lab1;
}

class Lab1 : public QWidget
{
    Q_OBJECT

public:
    explicit Lab1(QWidget *parent = 0);
    ~Lab1();

private slots:
    void on_buttonLine_clicked();
    void on_buttonRing_clicked();
    void on_buttonElipse_clicked();

    void on_buttonOpen_clicked();

    void on_buttonSave_clicked();

signals:
    void exit();

private:
    Ui::Lab1 *ui;
    QImage* image;
    QAction* actionOpen;
    QAction* actionSave;
};

#endif // LAB1_H
