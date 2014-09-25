#include "sesion.h"
#include "ui_sesion.h"
#include <QDebug>
#include <QSystemTrayIcon>
#include <QIcon>

Sesion::Sesion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sesion)
{
    ui->setupUi(this);

    ui->tableWidget->setEnabled(false);
    ui->tableWidget->setColumnCount(1);
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(0,QHeaderView::Stretch);
    header->setVisible(true);
    QStringList nameLabels;
    nameLabels<<"Aplicaciones";
    ui->tableWidget->setHorizontalHeaderLabels(nameLabels);

    this->windowsAnhadir = new dNewApp();

    ui->btnEditar->setEnabled(false);
    ui->btnEliminar->setEnabled(false);
    //ui->btnUp->setEnabled(false);
    //ui->btnDown->setEnabled(false);

    connect(this->windowsAnhadir,SIGNAL(getData(QString,QString,int,bool)),this,SLOT(newItem(QString,QString,int,bool)));
    connect(ui->btnAnhadir,SIGNAL(clicked()),this,SLOT(anhadirItem()));
    connect(ui->btnEditar,SIGNAL(clicked()),this,SLOT(editarItem()));
    connect(ui->btnEliminar,SIGNAL(clicked()),this,SLOT(eliminarItem()));
    connect(ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(activarEditarBtn(int,int)));
    connect(ui->tableWidget,SIGNAL(cellPressed(int,int)),this,SLOT(activarEditarBtn(int,int)));
    connect(ui->tableWidget,SIGNAL(cellActivated(int,int)),this,SLOT(activarEditarBtn(int,int)));
}

Sesion::~Sesion()
{
    delete ui;
}

void Sesion::anhadirItem()
{
    this->windowsAnhadir->cleanData();
    this->windowsAnhadir->show();
}

void Sesion::editarItem()
{
    emit this->initGetData(this->itemEditarX);
    this->windowsAnhadir->show();
}

void Sesion::activarEditarBtn(int y, int x)
{

    this->itemEditarX = x;
    this->itemEditarY = y;

    qDebug()<<x<<"\t"<<y;
    ui->btnEditar->setEnabled(true);
    ui->btnEliminar->setEnabled(true);
}

void Sesion::eliminarItem()
{
    ui->tableWidget->removeRow(this->itemEditarY);
}

void Sesion::newItem(QString nameApp, QString cmdApp, int timeContador,bool persistencia)
{
    wApp *item = new wApp();
    item->setData(ui->tableWidget->rowCount()-1,timeContador,nameApp,cmdApp,persistencia);
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,0,item);
    connect(this,SIGNAL(initGetData(int)),item,SLOT(getData(int)));
    connect(item,SIGNAL(getData(QString,QString,int,bool)),this->windowsAnhadir,SLOT(setData(QString,QString,int,bool)));
}
