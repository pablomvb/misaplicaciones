#include "itemdata.h"
#include "ui_itemdata.h"

itemData::itemData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemData)
{
    ui->setupUi(this);
    connect(ui->txtNombre,SIGNAL(textChanged(QString)),ui->txtNombreAplicacion,SLOT(setText(QString)));
    connect(ui->btnCancelar,SIGNAL(clicked()),this,SLOT(hide()));
    connect(ui->btnGuardar,SIGNAL(clicked()),this,SLOT(guardarDatos()));
    ui->txtNombreAplicacion->setText("");
    ui->checkBox->setVisible(false);
}

itemData::~itemData()
{
    delete ui;
}

void itemData::nuevaAplicacion()
{
    comando = "1";
    setVisible(true);
    editable(true);
    ui->txtComando->setText("");
    ui->txtNombre->setText("");
    ui->txtRetraso->setValue(0);
    ui->txtPresistencia->setChecked(false);
    ui->checkBox->setChecked(false);
}

void itemData::guardarDatos()
{
    QStringList datos;
    datos<<comando;
    datos<<ui->txtNombre->text();
    QStringList aplicacionCmdArg = ui->txtComando->text().split(" ");
    datos<<aplicacionCmdArg.value(0);
    aplicacionCmdArg.removeFirst();
    datos<<aplicacionCmdArg.join(";;");
    if(ui->txtPresistencia->isChecked()){
        datos<<"true";
    }
    else{
        datos<<"false";
    }
    datos<<QString().setNum(ui->txtRetraso->value());
    if(ui->checkBox->isChecked()){
        datos<<"APLICAR";
    }
    else{
        datos<<"NOAPLICAR";
    }
    emit getDatosAplicacion(datos.join("|||").toLatin1());
}

void itemData::editable(bool modo)
{
    ui->txtComando->setReadOnly(!modo);
    ui->txtNombre->setReadOnly(!modo);
    ui->txtRetraso->setReadOnly(!modo);
    ui->txtPresistencia->setCheckable(modo);
    ui->checkBox->setVisible(modo);
}
