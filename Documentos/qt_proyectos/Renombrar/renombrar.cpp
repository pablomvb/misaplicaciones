#include "renombrar.h"
#include "ui_renombrar.h"

Renombrar::Renombrar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Renombrar)
{
    ui->setupUi(this);
}

Renombrar::~Renombrar()
{
    delete ui;
}
