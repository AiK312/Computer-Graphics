#ifndef LAB4_H
#define LAB4_H
#define _USE_MATH_DEFINES

#include <QWidget>
#include <QMessageBox>
#include <QImage>
#include <QDialog>
#include <QMap>
#include <QRgb>
#include <QPainter>
#include <math.h>

const int n = 2;
const int m = 4;

namespace Ui {
class Lab4;
}

class Lab4 : public QDialog
{
    Q_OBJECT

public:
    explicit Lab4(QWidget *parent = 0);
    Lab4(QWidget *parent, QImage &imageFromMain);
    void Draw(int x[n][m], int y[n][m], int z[n][m]);
    ~Lab4();

signals:
    void endFunc();

private slots:

    void on_buttonFigure_clicked();
    void on_zoomButton_clicked();

    void on_turnButton_clicked();

    void on_translationButton_clicked();

private:
    Ui::Lab4 *ui;
    QImage *image;

    int Px[n][m];
    int Py[n][m];
    int Pz[n][m];


};

#endif // LAB4_H
