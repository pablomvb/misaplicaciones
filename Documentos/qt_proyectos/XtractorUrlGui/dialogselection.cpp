#include "dialogselection.h"
#include "ui_dialogselection.h"
#include <QDebug>

DialogSelection::DialogSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelection)
{
    ui->setupUi(this);
}

DialogSelection::~DialogSelection()
{
    delete ui;
}

QStringList DialogSelection::clave()
{
    QStringList r;

    if(ui->op1->isChecked()){
        r<<"1";
        r<<ui->lineEdit->text();
    } else if(ui->opIg->isChecked()){
        r<<"=";
    } else if(ui->opMa->isChecked()){
        r<<">";
    } else if(ui->opMe->isChecked()){
        r<<"<";
    }
    r<<QString().setNum(ui->spinBox->value());

    qDebug()<<r;

    return r;
}
