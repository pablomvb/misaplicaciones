#include "xtractor.h"
#include "ui_xtractor.h"

#include <QDebug>

Xtractor::Xtractor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Xtractor)
{
    ui->setupUi(this);
    ui->analisis->setObjectName("Inicio");
    ui->captura->setObjectName("Captura");
    connect(ui->visor,SIGNAL(currentChanged(int)),this,SLOT(fadeInWidget(int)));
    connect(ui->taskBar,SIGNAL(aplicacion(QString)),this,SLOT(cambiarAplicacion(QString)));
}

Xtractor::~Xtractor()
{
    delete ui;
}

void Xtractor::cambiarAplicacion(QString app)
{
    qDebug()<<app;
    if(app==ui->analisis->objectName()){
        ui->visor->setCurrentIndex(0);
    } else if(app==ui->captura->objectName()){
        ui->visor->setCurrentIndex(1);
    }
}

void Xtractor::fadeInWidget(int i)
{
    if (faderWidget)
        faderWidget->close();
    faderWidget = new FadeWidget(ui->visor->widget(i));
    faderWidget->start();
}
