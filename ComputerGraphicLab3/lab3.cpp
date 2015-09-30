#include "lab3.h"
#include "ui_lab3.h"

Lab3::Lab3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lab3)
{
    ui->setupUi(this);
}

Lab3::~Lab3()
{
    delete ui;
}
