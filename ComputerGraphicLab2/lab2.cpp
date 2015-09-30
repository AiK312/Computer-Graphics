#include "lab2.h"
#include "ui_lab2.h"

Lab2::Lab2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lab2)
{
    ui->setupUi(this);
}

Lab2::~Lab2()
{
    delete ui;
}
