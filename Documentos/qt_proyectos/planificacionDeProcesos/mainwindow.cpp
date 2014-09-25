#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgetselecionmetodo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    widgetSelecionMetodo* selectM = new widgetSelecionMetodo();
    connect(selectM,SIGNAL(getMetodo(QString)),this,SLOT(setMetodo(QString)));
    selectM->show();
    ui->setupUi(this);
    connect(this,SIGNAL(getMetodo(int)),ui->dataView,SLOT(setMetodo(int)));
    connect(this,SIGNAL(getMetodo(int)),ui->addData,SLOT(setMetodo(int)));
    connect(ui->addData,SIGNAL(getData(QStringList)),ui->dataView,SLOT(getData(QStringList)));
    connect(ui->dataView,SIGNAL(getResetIdProceso()),ui->addData,SLOT(setResetIdProceso()));
    connect(ui->addData,SIGNAL(getQtimeCiclo(int)),ui->dataView,SLOT(setQtime(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMetodo(QString metodo)
{
    this->metodoSelecionado = metodo;
    qDebug()<<this->metodoSelecionado;
    if(this->metodoSelecionado.count("FCFS")==1){
        this->mSelecionado = 1;
    }
    if(this->metodoSelecionado.count("SJF")==1){
        this->mSelecionado = 2;
    }
    if(this->metodoSelecionado.count("Basado en prioridades")==1){
        this->mSelecionado = 3;
    }
    if(this->metodoSelecionado.count("Round Robin")==1){
        this->mSelecionado = 4;
    }
    if(this->metodoSelecionado.count("Multicolas")==1){
        this->mSelecionado = 5;
    }
    if(this->metodoSelecionado.count("Multiprocesos")==1){
        this->mSelecionado = 6;
    }
    qDebug()<<this->mSelecionado;
    emit this->getMetodo(this->mSelecionado);
    this->setWindowTitle("Planificación de Procesos :: "+this->metodoSelecionado);
}

void MainWindow::on_actionFCFS_triggered()
{
    this->setMetodo("FCFS");
}

void MainWindow::on_actionSJF_triggered()
{
    this->setMetodo("SJF");
}

void MainWindow::on_actionBasado_en_prioridades_triggered()
{
    this->setMetodo("Basado en prioridades");
}

void MainWindow::on_actionRound_Robin_triggered()
{
    this->setMetodo("Round Robin");
}

void MainWindow::on_actionMulticolas_triggered()
{
    this->setMetodo("Multicolas");
}

void MainWindow::on_actionMultiprocesos_triggered()
{
    this->setMetodo("Multiprocesos");
}
