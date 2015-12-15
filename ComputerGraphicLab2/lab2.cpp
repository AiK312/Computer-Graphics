#include "lab2.h"
#include "ui_lab2.h"

Lab2::Lab2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lab2)
{
    image = new QImage();
    ui->setupUi(this);
    srand(time(0));
    connect(ui->buttonOpen, &QPushButton::clicked,
            ui->label, &QLabel::clear)

}

Lab2::~Lab2()
{
    delete ui;
}

void Lab2::on_pushButton_3_clicked()
{
    int P0X = ui->lineFirstX->text().toInt();
    int P1X = ui->lineSecondX->text().toInt();
    int P2X = ui->lineThirdX->text().toInt();
    int P3X = ui->lineFourX->text().toInt();

    int P0Y = ui->lineFirstY->text().toInt();
    int P1Y = ui->lineSecondY->text().toInt();
    int P2Y = ui->lineThirdY->text().toInt();
    int P3Y = ui->lineFourY->text().toInt();


    for(double t = 0; t < 1; t+=0.001)
    {
        int x = pow(t,3)*P3X+3*pow(t,2)*(1-t)*P2X+
                3*t*pow((1-t),2)*P1X+pow((1-t), 3)*P0X;
        int y = pow(t,3)*P3Y+3*pow(t,2)*(1-t)*P2Y+
                3*t*pow((1-t),2)*P1Y+pow((1-t), 3)*P0Y;

        image->setPixel(x, y, qRgb(0, 0, 255));
    }

    ui->label->setPixmap(QPixmap::fromImage(*image));
}

void Lab2::on_buttonOpen_clicked()
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

void Lab2::on_buttonSave_clicked()
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


void Lab2::on_polylineButton_clicked()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
        return;
    }

    int h = image->height();
    int w = image->width();

    coordinateList = new QMap<int, int>();
    QMap<int, int>::iterator it;
    int pointCount = ui->pointCount->text().toInt();

    for(int count = 0; count < pointCount; count++)
    {
         coordinateList->insert(1+rand()%(w-1), 1+rand()%(h-1));
    }

    for(it = coordinateList->begin(); it != coordinateList->end()-1; ++it)
    {
        int x1 = it.key();
        int y1 = it.value();
        it++;
        int x2 = it.key();
        int y2 = it.value();
        it--;

        double x, y;

        for(x = x1; x < x2; x+=0.001)
        {
            y = ((x-x1)*(y2-y1)) / (x2-x1) + y1;
            image->setPixel(x, y, qRgb(0, 255, 0));
        }
        ui->label->setPixmap(QPixmap::fromImage(*image));
    }

}

void Lab2::on_antialiasingButton_clicked()
{

    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
        return;
    }

    if(coordinateList->isEmpty())
    {
        QMessageBox::information(this, "Warning!", "Сначала постройте ломаную");
        return;
    }

    QMap<int, int>::iterator it;        

    for(it = coordinateList->begin(); it != coordinateList->end()-1; it++)
    {
        int xCur = it.key();
        int yCur = it.value();
        int xPre=0, yPre=0, xNext=0, yNext=0, xNextNext=0, yNextNext=0;

        if(it == coordinateList->begin())
        {
            xPre = xCur;
            yPre = yCur;
            it++;
        }
        else
        {
            it--;
            xPre = it.key();
            yPre = it.value();
            it += 2;
        }

        xNext = it.key();
        yNext = it.value();
        it--;

        if(it == coordinateList->end()-2)
        {
            xNextNext = xNext;
            yNextNext = yNext;
        }
        else
        {
            it += 2;
            xNextNext = it.key();
            yNextNext = it.value();
            it -=2;
        }

        int x, y;


        for(double t=0; t<=1; t+=0.001)
        {
            int a0 = (xPre + 4*xCur + xNext) / 6;
            int a1 = (-xPre + xNext) / 2;
            int a2 = (xPre - 2*xCur + xNext) / 2;
            int a3 = (-xPre + 3*xCur - 3*xNext + xNextNext) / 6;

            int b0 = (yPre + 4*yCur + yNext) / 6;
            int b1 = (-yPre + yNext) / 2;
            int b2 = (yPre - 2*yCur + yNext) / 2;
            int b3 = (-yPre + 3*yCur - 3*yNext + yNextNext) / 6;

            x = ((a3*t+a2)*t+a1)*t+a0;
            y = ((b3*t+b2)*t+b1)*t+b0;

            image->setPixel(x, y, qRgb(255, 0, 0));
        }
        ui->label->setPixmap(QPixmap::fromImage(*image));
    }
}
