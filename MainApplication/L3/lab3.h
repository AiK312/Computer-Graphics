#ifndef LAB3_H
#define LAB3_H

#include <QWidget>
#include <QMessageBox>
#include <QImage>
#include <QDialog>
#include <QMap>
#include <QRgb>
#include <QPainter>
#include <time.h>

namespace Ui {
class Lab3;
}

class Lab3 : public QDialog
{
    Q_OBJECT

public:
    explicit Lab3(QWidget *parent = 0);
    Lab3(QWidget *parent, QImage &imageFromMain);
    ~Lab3();

signals:
    void endFunc();

private slots:
    void on_windowButton_clicked();
    void Colen_Sutherland(int, int, int, int);
    int VCODE(int, int);



    void on_areaButton_clicked();

    void on_paintButton_clicked();

private:
    Ui::Lab3 *ui;
    QImage *image;
    struct RECT
    {
        int x_min, y_min, x_max, y_max;
    };
    struct POINT
    {
        int x, y;
    };
    POINT *c = NULL;
    RECT *rect = NULL;

    QMap<int, int> *coordinateList;

};

#endif // LAB3_H
