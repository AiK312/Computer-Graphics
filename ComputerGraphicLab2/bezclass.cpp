#include "bezclass.h"
#include "ui_bezclass.h"

BezClass::BezClass(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BezClass)
{
    ui->setupUi(this);
    actionOpen = new QAction(this);
    actionSave = new QAction(this);
    image = new QImage;

    actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ui->centralWidget->addAction(actionOpen);

    actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->centralWidget->addAction(actionSave);


    connect(actionOpen, SIGNAL(triggered(bool)),
            this, SLOT(menuOpenFile()));
    connect(actionSave, SIGNAL(triggered(bool)),
            this, SLOT(menuSaveFile()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)),
            this, SLOT(menuOpenFile()));
    connect(ui->actionSave, SIGNAL(triggered(bool)),
            this, SLOT(menuSaveFile()));
    connect(ui->actionExit, SIGNAL(triggered(bool)),
            this, SLOT(menuExit()));
}

BezClass::~BezClass()
{
    delete ui;
}

void BezClass::menuExit()
{
    emit exit();
}

void BezClass::menuSaveFile()
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

void BezClass::menuOpenFile()
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

void BezClass::on_pushButton_clicked()
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

        image->setPixel(x, y, qRgb(0, 255, 0));
    }

    ui->label->setPixmap(QPixmap::fromImage(*image));
}
