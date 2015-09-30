#include "lab1.h"
#include "ui_lab1.h"

Lab1::Lab1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lab1)
{
    image = new QImage();
    ui->setupUi(this);
}

Lab1::~Lab1()
{
    delete ui;
}

void Lab1::on_buttonLine_clicked()
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

    //вертикальная линия
    if(dx == 0)
    {
        x = x1;
        y = y1;
        while(y < y2)
        {
            image->setPixel(x, y, qRgb(255, 0, 0));
            y++;
        }
    }
    //горизонтальная линия
    if(dy == 0)
    {
        y = y1;
        x = x1;
        while(x < x2)
        {
            image->setPixel(x, y, qRgb(255, 0, 0));
            x++;
        }
    }
    //убывающая линия
    if((x1 < x2) && (y1 < y2))
    {
        x = x1;
        y = y1;
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
    }
    //возрастающая линия
    else if((x1 < x2) && (y1 > y2))
    {
        x = x1;
        y = y1;
        image->setPixel(x, y, qRgb(255, 0, 0));

        while(x < x2)
        {
            x++;
            if(p < 0)
            {
                p += twoDy;
            }
            else
            {
                y--;
                p += twoDyMinusDx;
            }
            image->setPixel(x, y, qRgb(255, 0, 0));
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(*image));
}

void Lab1::on_buttonRing_clicked()
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

void Lab1::on_buttonElipse_clicked()
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



void Lab1::on_buttonOpen_clicked()
{
    QString filename = QFileDialog::getOpenFileName(0, "Open File", "D:", "*.bmp");
    if(!filename.isNull())
    {
        image->load(filename);
        ui->label->setPixmap(QPixmap(filename));
    }
    else
        return;
}

void Lab1::on_buttonSave_clicked()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
    }
    else
    {
        QString *filter = new QString(".bmp");
        QString filename = QFileDialog::getSaveFileName(0, "Save file", "D:", *filter);
        filename += filter;
        if(!filename.isNull())
        {
            image->save(filename);
        }
    }
}
