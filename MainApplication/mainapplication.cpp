#include "mainapplication.h"
#include "ui_mainapplication.h"

MainApplication::MainApplication(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainApplication)
{
    ui->setupUi(this);
    image = new QImage();
    L1 = new Lab1(this, *image);
    actionOpen = new QAction(this);
    actionSave = new QAction(this);
    actionSaveAs = new QAction(this);

    actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ui->centralWidget->addAction(actionOpen);

    actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->centralWidget->addAction(actionSave);

    actionSaveAs->setShortcut((QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S)));
    ui->centralWidget->addAction(actionSaveAs);

    connect(actionOpen, SIGNAL(triggered(bool)),
            this, SLOT(openFile()));
    connect(actionSave, SIGNAL(triggered(bool)),
            this, SLOT(saveFile()));
    connect(actionSaveAs, SIGNAL(triggered(bool)),
            this, SLOT(saveAsFile()));

    connect(ui->actionOpen, SIGNAL(triggered(bool)),
            this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered(bool)),
            this, SLOT(saveFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)),
            this, SLOT(saveAsFile()));
    connect(ui->actionExit, SIGNAL(triggered(bool)),
            this, SLOT(exitApp()));

    connect(ui->actionLab1, SIGNAL(triggered(bool)),
            this, SLOT(runLab1()));
    connect(L1, SIGNAL(endFucn()),
            this, SLOT(setLabelImage()));

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
