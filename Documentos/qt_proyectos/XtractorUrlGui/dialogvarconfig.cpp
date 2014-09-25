#include "dialogvarconfig.h"
#include "ui_dialogvarconfig.h"
#include <QFile>

DialogVarConfig::DialogVarConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVarConfig)
{
    ui->setupUi(this);
    setWindowTitle("Editor de Parametros");
    cargarDatos();
    connect(ui->btnAnhadir,SIGNAL(clicked()),this,SLOT(nuevoscript()));
    connect(ui->seleccionScript,SIGNAL(currentIndexChanged(int)),this,SLOT(cambiarscript(int)));
    connect(ui->btnBox,SIGNAL(accepted()),this,SLOT(guardar()));
    connect(ui->btnEliminar,SIGNAL(clicked()),this,SLOT(eliminar()));
    estado = 0;
    index = 0;
}

DialogVarConfig::~DialogVarConfig()
{
    delete ui;
}

void DialogVarConfig::cargarDatos()
{
    QFile archivoScripts;
    archivoScripts.setFileName("scriptsconfig");
    if(archivoScripts.open(QIODevice::ReadOnly)){
        datos = QString(archivoScripts.readAll()).split("\n");
        for(int i = 0; i<datos.count(); i++){
            if(datos.value(i).count()==0){
                datos.removeAt(i);
                i--;
            }
        }
        ui->seleccionScript->clear();
        for(int i=0; i<datos.count();i++){
            ui->seleccionScript->addItem(datos.value(i).split(":::").value(0));
        }
        ui->seleccionScript->setCurrentText("Seleccion un grupo de parametros");
    }
    archivoScripts.close();
    enableTxt(false);
    cambiarscript(0);
}

void DialogVarConfig::enableTxt(bool std)
{
    ui->txt1->setEnabled(std);
    ui->txt2->setEnabled(std);
    ui->txt3->setEnabled(std);
    ui->txt4->setEnabled(std);
    ui->txt5->setEnabled(std);
    ui->txt6->setEnabled(std);
    ui->txt7->setEnabled(std);
}

void DialogVarConfig::nuevoscript()
{
    enableTxt(true);
    ui->seleccionScript->setEnabled(false);
    ui->txt1->setReadOnly(false);
    ui->txt1->clear();
    ui->txt2->clear();
    ui->txt3->clear();
    ui->txt4->clear();
    ui->txt5->clear();
    ui->txt6->clear();
    ui->txt7->clear();
    ui->txt8->clear();
    ui->txt9->clear();
    ui->txt10->clear();
    estado = 2;
}

void DialogVarConfig::cambiarscript(int i)
{
    estado = 1;
    QStringList d = datos.value(i).split(":::");
    enableTxt(true);
    ui->txt1->setReadOnly(true);
    index = i;
        ui->txt1->setText(d.value(0));
        ui->txt2->setCurrentText(d.value(1));
        ui->txt3->setText(d.value(2));
        ui->txt4->setText(d.value(3));
        ui->txt5->setText(d.value(4));
        ui->txt6->setText(d.value(5));
        ui->txt7->setText(d.value(6));
        ui->txt8->setText(d.value(7));
        ui->txt9->setText(d.value(8));
        ui->txt10->setText(d.value(9));
}

void DialogVarConfig::guardar()
{
    QStringList retorno;
    retorno<<ui->txt1->text();
    retorno<<ui->txt2->currentText();
    retorno<<ui->txt3->text();
    retorno<<ui->txt4->text();
    retorno<<ui->txt5->text();
    retorno<<ui->txt6->text();
    retorno<<ui->txt7->text();
    retorno<<ui->txt8->text();
    retorno<<ui->txt9->text();
    retorno<<ui->txt10->text();
    if(estado == 2){
        datos.append(retorno.join(":::"));
    } else if(estado == 1){
        datos.removeAt(index);
        datos.append(retorno.join(":::"));
    }
    QFile f;
    f.setFileName("scriptsconfig");
    f.remove();
    f.open(QIODevice::WriteOnly);
    f.write(datos.join("\n").toLatin1());
    f.waitForBytesWritten(0);
    f.close();
}

void DialogVarConfig::eliminar()
{
    datos.removeAt(index);
    QFile f;
    f.setFileName("scriptsconfig");
    f.remove();
    f.open(QIODevice::WriteOnly);
    f.write(datos.join("\n").toLatin1());
    f.waitForBytesWritten(0);
    f.close();
    cargarDatos();
}
