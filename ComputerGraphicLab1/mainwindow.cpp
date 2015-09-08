#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    image = new QImage();
    ui->setupUi(this);

    connect(ui->actionOpen, SIGNAL(triggered(bool)),
            this, SLOT(menuOpenFile()));
    connect(ui->actionSave, SIGNAL(triggered(bool)),
            this, SLOT(menuSaveFile()));
    connect(ui->actionClose, SIGNAL(triggered(bool)),
            this, SLOT(menuExit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineButton_clicked()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
        return;
    }
    int x1, y1, x2, y2;
    x1 = ui->lineX1->text().toInt();
    y1 = ui->lineY1->text().toInt();
    x2 = ui->lineX2->text().toInt();
    y2 = ui->lineY2->text().toInt();

    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
    int x, y;

    double tan = double(dy) / double(dx);
    QMessageBox::information(this, "S", QString::number(tan));

    if(x1 > x2)
    {
        x = x2;
        y = y2;
        x2 = x1;
        y2 = y1;
    }
    else
    {
        x = x1;
        y = y1;
    }
    image->setPixel(x, y, qRgb(255, 0, 0));

    while(x < x2)
    {
        x++;
        if(p < 0)
            p += twoDy;
        else
        {
            y++;
            p += twoDyMinusDx;
        }
        image->setPixel(x, y, qRgb(255, 0, 0));
    }


    if(dx == 0)
    {
        x = x1;
        while(y < y2)
        {
            image->setPixel(x, y, qRgb(255, 0, 0));
            y++;
        }
    }
    if(dy == 0)
    {
        y = y1;
        while(x < x2)
        {
            image->setPixel(x, y, qRgb(255, 0, 0));
            x++;
        }
    }



    ui->label->setPixmap(QPixmap::fromImage(*image));
}

void MainWindow::menuOpenFile()
{
    QString filename = QFileDialog::getOpenFileName(0, "Open File", "D:", "*.bmp");
    if(!filename.isNull())
    {
        image->load(filename);
        ui->label->setPixmap(QPixmap(filename));
    }
    else
    {
        QMessageBox::information(this, "Error", "Error open file");
        return;
    }
}

void MainWindow::menuSaveFile()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
    }
    else
    {
        QString *filter = new QString(".bmp");
        QString filename = QFileDialog::getSaveFileName(0, "Save file", "D:", *filter);
        if(!filename.isNull())
        {
            image->save(filename);
        }
    }
}

void MainWindow::menuExit()
{
    emit exit();
}


void MainWindow::on_pushButton_clicked()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
        return;
    }
    int xc, yc, r, x, y;
    xc = ui->lineX->text().toInt();
    yc = ui->lineY->text().toInt();
    r = ui->lineR->text().toInt();
    double tangle;

    for(tangle = 0; tangle < 360; tangle++)
    {
        x = xc + r * cos(tangle);
        y = yc + r * sin(tangle);
        image->setPixel(x, y, qRgb(0, 255, 0));
    }
    ui->label->setPixmap(QPixmap::fromImage(*image));

}

void MainWindow::on_pushButton_2_clicked()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
        return;
    }
    double x = 0, xc = 0, yc = 0, rx = 0, ry = 0;
    double ya = 0.0, yb = 0.0;
    xc = ui->lineXC->text().toInt();
    yc = ui->lineYC->text().toInt();
    rx = ui->lineRX->text().toInt();
    ry = ui->lineRY->text().toInt();
    int end = xc + rx;
    int start = xc - rx;
    for(x = start; x <= end; x++)
    {

        ya = yc + ry * sqrt(1 - pow((x - xc)/rx, 2));
        yb = yc - ry * sqrt(1 - pow((x - xc)/rx, 2));
        image->setPixel(x, ya, qRgb(0, 0, 255));
        image->setPixel(x, yb, qRgb(0, 0, 255));

    }

    ui->label->setPixmap(QPixmap::fromImage(*image));

}
