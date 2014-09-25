#include "dialogseleciface.h"
#include "ui_dialogseleciface.h"

DialogSelecIface::DialogSelecIface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSelecIface)
{
    ui->setupUi(this);
}

DialogSelecIface::~DialogSelecIface()
{
    delete ui;
}

void DialogSelecIface::setDataIface(QStringList data)
{
    ui->comboBox->addItems(data);
}

QString DialogSelecIface::getIfaceSelec()
{
    return ui->comboBox->currentText();
}
