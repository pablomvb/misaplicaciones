#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnConectar,SIGNAL(clicked()),this,SLOT(conectar()));
    connect(ui->btnDesconectar,SIGNAL(clicked()),this,SLOT(desconectar()));
    ui->btnDesconectar->setEnabled(false);

    cliente =  new QTcpSocket();
    inputData = new QUdpSocket();
    connect(inputData,SIGNAL(readyRead()),this,SLOT(inputImagen()));
    inputData->bind(6591);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeData(QString data)
{
    data.append("\n");
    cliente->write(data.toLatin1());
    cliente->waitForBytesWritten(5);
    qDebug()<<"cmd_send: "<<data;
}

void MainWindow::conectar()
{
    cliente->connectToHost(ui->ipDestono->text(),6590);
    if(!cliente->waitForConnected(10)){
        QMessageBox msj;
        msj.setInformativeText("No se puedo conectar con: "+ui->ipDestono->text());
        msj.exec();
    }
    else{
        ui->btnConectar->setEnabled(false);
        ui->btnDesconectar->setEnabled(true);
        connect(cliente,SIGNAL(disconnected()),this,SLOT(desconectar()));
        writeData("1|*|INICIAR");
    }
}

void MainWindow::desconectar()
{
    cliente->abort();
    disconnect(cliente,SIGNAL(disconnected()),this,SLOT(desconectar()));
    ui->btnConectar->setEnabled(true);
    ui->btnDesconectar->setEnabled(false);
}

void MainWindow::inputImagen()
{
    qDebug()<<inputData->readAll();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug()<<size();
}
