#include "mainapplication.h"
#include "ui_mainapplication.h"

MainApplication::MainApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApplication)
{
    ui->setupUi(this);
    image = new QImage();
    L1 = new Lab1(this, *image);
    L2 = new Lab2(this, *image);
    actionOpen = new QAction(this);
    actionSave = new QAction(this);
    actionSaveAs = new QAction(this);

    actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ui->centralWidget->addAction(actionOpen);

    actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->centralWidget->addAction(actionSave);

    actionSaveAs->setShortcut((QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S)));
    ui->centralWidget->addAction(actionSaveAs);


    connect(actionOpen, &QAction::triggered,
            this, &MainApplication::openFile);
    connect(actionSave, &QAction::triggered,
            this, &MainApplication::saveFile);
    connect(actionSaveAs, &QAction::triggered,
            this, &MainApplication::saveAsFile);

    connect(ui->actionOpen, &QAction::triggered,
            this, &MainApplication::openFile);
    connect(ui->actionSave, &QAction::triggered,
            this, &MainApplication::saveFile);
    connect(ui->actionSaveAs, &QAction::triggered,
            this, &MainApplication::saveAsFile);
    connect(ui->actionExit, &QAction::triggered,
            this, &MainApplication::exitApp);

    connect(ui->actionLab1, &QAction::triggered,
            this, &MainApplication::runLab1);
    connect(L1, &Lab1::endFunc,
            this, &MainApplication::setLabelImage);

    connect(ui->actionLab2, &QAction::triggered,
            this, &MainApplication::runLab2);
    connect(L2, &Lab2::endFunc,
            this, &MainApplication::setLabelImage);

}

MainApplication::~MainApplication()
{
    delete ui;
}

void MainApplication::openFile()
{
    filename = QFileDialog::getOpenFileName(0, "Open File", "D:", "*.bmp");
    if(!filename.isNull())
    {
        image->load(filename);
        ui->label->setPixmap(QPixmap(filename));
        ui->menuLabs->setEnabled(true);
        ui->actionSave->setEnabled(true);
        ui->actionSaveAs->setEnabled(true);
        ui->actionClean->setEnabled(true);
    }
    else
        return;
}

void MainApplication::saveFile()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
    }
    else
    {
        image->save(filename);
    }
}

void MainApplication::saveAsFile()
{
    if(image->isNull())
    {
        QMessageBox::information(this, "Warning!", "Сначала надо открыть файл");
    }
    else
    {
        QString *filter = new QString(".bmp");
        filename = QFileDialog::getSaveFileName(0, "Save file", "D:", *filter);
        filename += filter;
        if(!filename.isNull())
        {
            image->save(filename);
        }
    }
}

void MainApplication::exitApp()
{
    emit exit();
}

void MainApplication::setLabelImage()
{
    ui->label->setPixmap(QPixmap::fromImage(*image));
}

void MainApplication::runLab1()
{
    L1->show();
}

void MainApplication::runLab2()
{
    L2->show();
}
