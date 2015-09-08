#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_lineButton_clicked();
    void menuOpenFile();
    void menuSaveFile();
    void menuExit();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void exit();

private:
    Ui::MainWindow *ui;
    QImage* image;
};

#endif // MAINWINDOW_H
