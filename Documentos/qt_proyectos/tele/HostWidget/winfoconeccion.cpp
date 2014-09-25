#include "winfoconeccion.h"
#include "ui_winfoconeccion.h"

wInfoConeccion::wInfoConeccion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wInfoConeccion)
{
    ui->setupUi(this);
    setEstado(0);
}

wInfoConeccion::~wInfoConeccion()
{
    delete ui;
}

void wInfoConeccion::setEstado(int estado)
{
    QString colorBoton;
    QString label;
    switch (estado) {
    case 0:
        colorBoton = "background-color: rgb(116, 116, 116);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(34, 34, 34);";
        label = "Desconetado";
        break;
    case 1:
        colorBoton = "background-color: rgb(0, 231, 0);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(0, 132, 0);";
        label = "Conectado";
        break;
    case 2:
        colorBoton = "background-color: rgb(255, 77, 0);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(255, 43, 0);";
        label = "En espera";
        break;
    case 3:
        colorBoton = "background-color: rgb(255, 0, 0);border-style: outset;border-width: 1px;border-radius: 2px;border-color: rgb(174, 0, 0);";
        label = "Error";
        break;
    }
    ui->vEstadoColor->setStyleSheet(colorBoton);
    ui->vEstadoDescripcion->setText(label);
}
