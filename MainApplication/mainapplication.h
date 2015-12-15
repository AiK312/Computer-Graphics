#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QMainWindow>
#include <QAction>
#include "L1/lab1.h"
#include "L2/lab2.h"
#include "L3/lab3.h"
#include "L4/lab4.h"
#include <QScrollArea>

namespace Ui {
class MainApplication;
}

class MainApplication : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainApplication(QWidget *parent = 0);
    ~MainApplication();

private:
    Ui::MainApplication *ui;
    QImage* image;
    QImage* old_image;
    Lab1 *L1;
    Lab2 *L2;
    Lab3 *L3;
    Lab4 *L4;
    QAction* actionOpen;
    QAction* actionSave;
    QAction* actionSaveAs;
    QString filename;
    QScrollArea *scr;

private slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void exitApp();
    void setOldImage();
    void setLabelImage();
    void runLab1();
    void runLab2();
    void runLab3();
    void runLab4();

signals:
    void exit();
};

#endif // MAINAPPLICATION_H
