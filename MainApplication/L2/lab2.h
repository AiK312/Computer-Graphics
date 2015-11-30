#ifndef LAB2_H
#define LAB2_H

#include <QWidget>
#include <QFileDialog>
#include <QDialog>
#include <QMessageBox>
#include <QAction>
#include <QImage>
#include "math.h"
#include <QMap>
#include <time.h>


namespace Ui {
class Lab2;
}

class Lab2 : public QDialog
{
    Q_OBJECT

public:
    explicit Lab2(QWidget *parent = 0);
	Lab2(QWidget *parent, QImage &imageFromMain);
    ~Lab2();   

private slots:
    void on_pushButton_3_clicked();    
    void on_polylineButton_clicked();
    void on_antialiasingButton_clicked();
	
signals:
	void exit();
	void endFunc();

private:
    Ui::Lab2 *ui;
    QImage *image;
    QMap<int, int> *coordinateList;
};

#endif // LAB2_H
