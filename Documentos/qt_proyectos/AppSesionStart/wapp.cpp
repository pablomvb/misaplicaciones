#include "wapp.h"
#include "ui_wapp.h"

wApp::wApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wApp)
{
    ui->setupUi(this);
    this->run = false;

    this->timerEspera = new QTimer(this);
    this->timerEspera->setSingleShot(true);

    connect(ui->chkBucle,SIGNAL(toggled(bool)),this,SLOT(cambioPersistencia(bool)));
    connect(this->timerEspera,SIGNAL(timeout()),this,SLOT(startApp()));
}

wApp::~wApp()
{
    delete ui;
}

void wApp::setData(int index, int tDuracion, QString nameApp, QString cmdApp,bool persistencia)
{
    this->index = index;
    this->timerDuracion = tDuracion;
    this->timerEspera->setInterval(this->timerDuracion * 1000);
    this->timerEspera->start();
    this->nameApp = nameApp;
    this->cmdApp = cmdApp;
    this->persistencia = persistencia;
    ui->chkBucle->setChecked(persistencia);
    ui->txtAplicacionName->setText(this->nameApp);
}

int wApp::getDataDuracion()
{
    return this->timerDuracion;
}

QString wApp::getDataNameApp()
{
    return this->nameApp;
}

QString wApp::getDataCmdApp()
{
    return this->cmdApp;
}

bool wApp::getDataPersistencia()
{
    return this->persistencia;
}

void wApp::getData(int index)
{
    if(index == this->index){
        emit this->getData(this->nameApp,this->cmdApp,this->timerDuracion,this->persistencia);
    }
}

void wApp::cambioPersistencia(bool persistencia)
{
    this->persistencia = persistencia;
}

void wApp::setPID(QString pid)
{
    this->pid = pid;
}

void wApp::startApp()
{
    this->aplicacionRun = new AppThread(this->nameApp,this->cmdApp,this->persistencia,this);
    connect(this->aplicacionRun,SIGNAL(pid(QString)),this,SLOT(setPID(QString)));
    connect(this->aplicacionRun,SIGNAL(estadoProceso(int)),this,SLOT(estadoWidget(int)));
    connect(ui->btnStart,SIGNAL(clicked()),this->aplicacionRun,SLOT(run()));
    connect(ui->btnStop,SIGNAL(clicked()),this->aplicacionRun,SLOT(stop()));
    connect(ui->btnForceStop,SIGNAL(clicked()),this->aplicacionRun,SLOT(forceStop()));
    connect(this->aplicacionRun,SIGNAL(signalError(int)),this,SLOT(ErrorApp(int)));
    connect(ui->chkBucle,SIGNAL(toggled(bool)),this->aplicacionRun,SLOT(cambioEstadoBucle(bool)));
    connect(ui->btnReset,SIGNAL(clicked()),this->aplicacionRun,SLOT(resetApp()));
    this->aplicacionRun->run();
}

void wApp::ErrorApp(int ErrorA)
{
    this->codeExit = ErrorA;
}

void wApp::estadoWidget(int estado)
{
    QString lbl;
    lbl = this->nameApp + "  :  ";

    switch (estado) {
    case 1:
        ui->btnStart->setEnabled(false);
        ui->btnStop->setEnabled(true);
        ui->btnEstado->setStyleSheet("background-color: rgb(0, 212, 0);border-style: outset;border-radius: 2px;");
        lbl = lbl + "Ok (PID: "+pid+")";
        break;
    case 2:
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
        ui->btnEstado->setStyleSheet("background-color: red;border-style: outset;border-radius: 2px;");
        lbl = lbl + "Stop / "+ "codigo de error = " + QString().number(this->codeExit);
        break;
    case 3:
        this->estadoWidget(2);
        lbl = lbl + "codigo de error = " + QString().number(this->codeExit);
        break;
    default:
        break;
    }

    qDebug()<<estado;

    ui->txtAplicacionName->setText(lbl);
}

void wApp::removerWidget()
{
    ui->chkBucle->setChecked(false);
    this->aplicacionRun->removeApp();
    this->~wApp();
}
