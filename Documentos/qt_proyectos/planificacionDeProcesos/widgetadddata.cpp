#include "widgetadddata.h"
#include "ui_widgetadddata.h"

widgetAddData::widgetAddData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetAddData)
{
    ui->setupUi(this);
    connect(ui->btnAgregar,SIGNAL(clicked()),this,SLOT(btnAdd()));
    connect(ui->txtBoxQ,SIGNAL(editingFinished()),this,SLOT(qTime()));
    connect(ui->txtBoxQ,SIGNAL(valueChanged(int)),this,SLOT(qTime(int)));
    this->nProceso = 0;
    QStringList listaPrioridades;
    listaPrioridades<<"Tiempo Real"<<"Muy Alta"<<"Alta"<<"Normal"<<"Baja"<<"Muy Baja";
    ui->txtBoxPrioridad->addItems(listaPrioridades);
    ui->txtBoxClasificacio->addItems(QStringList()<<"Primer plano"<<"Segundo plano");
    ui->txtBoxPrioridad->setVisible(false);
    ui->label_3->setVisible(false);
    ui->lblQ->setVisible(false);
    ui->txtBoxQ->setVisible(false);
    ui->lblClasificacion->setVisible(false);
    ui->txtBoxClasificacio->setVisible(false);

}

widgetAddData::~widgetAddData()
{
    delete ui;
}

void widgetAddData::setIdProceso()
{
    QString num;
    this->nProceso++;
    num.setNum(this->nProceso);
    ui->txtIdProceso->setText("P"+num);
    ui->txtBoxPrioridad->setCurrentIndex(3);
}

void widgetAddData::setMetodo(int metodo)
{
    this->metodo = metodo;
    this->nProceso = 0;
    this->setIdProceso();
    ui->txtBoxLlegada->setMinimum(0);
    ui->txtBoxLlegada->setValue(0);

    bool prioridad = false;
    bool roundRobin = false;
    bool multicolas = false;

    if(this->metodo==3){
        prioridad = true;
    }

    if(this->metodo==4){
        roundRobin = true;
    }

    if(this->metodo==5){
        multicolas = true;
        roundRobin = true;
    }

    ui->txtBoxPrioridad->setVisible(prioridad);
    ui->label_3->setVisible(prioridad);
    ui->lblQ->setVisible(roundRobin);
    ui->txtBoxQ->setVisible(roundRobin);
    ui->lblClasificacion->setVisible(multicolas);
    ui->txtBoxClasificacio->setVisible(multicolas);

    qDebug()<<"wad: "<<this->metodo;
}

void widgetAddData::btnAdd()
{
    QStringList l;
    l<<ui->txtIdProceso->text();
    l<<ui->txtBoxLlegada->text();
    l<<ui->txtDuracionProceso->text();

    if(this->metodo==3){
        l<<ui->txtBoxPrioridad->currentText();
    }

    if(this->metodo==4){
        l<<ui->txtBoxQ->text();
    }

    if(this->metodo==5){
        l<< ui->txtBoxClasificacio->currentText();
        qDebug()<<ui->txtBoxClasificacio->currentText();
    }

    this->setIdProceso();
    emit this->getData(l);
    ui->txtBoxLlegada->setMinimum(ui->txtBoxLlegada->value()+1);
}

void widgetAddData::setResetIdProceso()
{
    this->nProceso = 0;
    this->setIdProceso();
    ui->txtBoxLlegada->setMinimum(0);
    ui->txtBoxLlegada->setValue(0);
}

void widgetAddData::qTime()
{
    emit this->getQtimeCiclo(ui->txtBoxQ->value());
}

void widgetAddData::qTime(int q)
{
    emit this->getQtimeCiclo(q);
}
