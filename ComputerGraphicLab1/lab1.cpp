#include "lab1.h"
#include "ui_lab1.h"

Lab1::Lab1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lab1)
{
    ui->setupUi(this);
}

Lab1::~Lab1()
{
    delete ui;
}
