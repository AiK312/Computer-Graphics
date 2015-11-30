#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QMainWindow>
#include <QAction>
//#include <QString>
#include "L1/lab1.h"
#include "L2/lab2.h"

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
    Lab1 *L1;
    Lab2 *L2;
    QAction* actionOpen;
    QAction* actionSave;
    QAction* actionSaveAs;
    QString filename;

private slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void exitApp();
    void setLabelImage();
    void runLab1();
    void runLab2();

signals:
    void exit();
};

#endif // MAINAPPLICATION_H
