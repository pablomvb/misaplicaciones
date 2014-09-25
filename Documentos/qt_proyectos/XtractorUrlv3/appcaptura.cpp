#include "appcaptura.h"
#include "ui_appcaptura.h"

AppCaptura::AppCaptura(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppCaptura)
{
    ui->setupUi(this);
}

AppCaptura::~AppCaptura()
{
    delete ui;
}
