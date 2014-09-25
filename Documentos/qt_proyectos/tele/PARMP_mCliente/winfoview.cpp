#include "winfoview.h"
#include "ui_winfoview.h"

wInfoView::wInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wInfoView)
{
    ui->setupUi(this);
}

wInfoView::~wInfoView()
{
    delete ui;
}

void wInfoView::setEstado(int estado)
{
    switch (estado) {
    case 0:
        ui->infoColor->setStyleSheet("background-color: rgb(116, 116, 116);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(34, 34, 34);");
        ui->lblEstado->setText("Desconetado");
        break;
    case 1:
        ui->infoColor->setStyleSheet("background-color: rgb(0, 231, 0);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(0, 132, 0);");
        ui->lblEstado->setText("Conectado");
        break;
    case 2:
        ui->infoColor->setStyleSheet("background-color: rgb(255, 77, 0);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(255, 43, 0);");
        ui->lblEstado->setText("En espera");
        break;
    case 3:
        ui->infoColor->setStyleSheet("background-color: rgb(255, 0, 0);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(174, 0, 0);");
        ui->lblEstado->setText("Error");
        break;
    }
}

/*
 * desconetado 0
 * conectado   1
 * en espera   2
 * error       3
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
