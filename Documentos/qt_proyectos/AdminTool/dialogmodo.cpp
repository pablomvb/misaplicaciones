#include "dialogmodo.h"
#include "ui_dialogmodo.h"

DialogModo::DialogModo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModo)
{
    ui->setupUi(this);
}

DialogModo::~DialogModo()
{
    delete ui;
}

int DialogModo::getModo()
{
    int m;

    if(ui->radioButton->isChecked()){
        m = 1;
    }
    else{
        if(ui->radioButton_2->isChecked()){
            m = 2;
        }
    }

    return m;
}
