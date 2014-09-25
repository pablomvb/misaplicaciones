#include "sesion.h"
#include <QDebug>

Sesion::Sesion(QObject *parent) :
    QObject(parent)
{
    hilo = new QThread();
    comando = new QProcess();
    servidor =  new QTcpServer();
    comando->moveToThread(hilo->thread());
    connect(comando,SIGNAL(readyReadStandardError()),this,SLOT(leerError()));
    connect(comando,SIGNAL(readyReadStandardOutput()),this,SLOT(leerStdout()));
    servicioOcupado = false;
}

void Sesion::iniciarServicio()
{
    iniciarServidor();
    qDebug()<<"TERMINAL REMOTA : Iniciado";
}

void Sesion::iniciarServidor()
{
    if(!servidor->listen(QHostAddress::Any,6901)){
        qDebug()<<"SERVIDOR : Error al iniciar ...";
        exit(0);
    } else {
        connect(servidor,SIGNAL(newConnection()),this,SLOT(nuevoCliente()));
        qDebug()<<"SERVIDOR : Esperando clientes";
    }
}

void Sesion::nuevoCliente()
{
    if(!servicioOcupado){
        cliente = servidor->nextPendingConnection();
        connect(cliente,SIGNAL(disconnected()),this,SLOT(despacharCliente()));
        servicioOcupado = true;
        qDebug()<<"SERVIDOR : Nuevo Cliente : Aceptado";
        qDebug()<<"TERMINAL REMOTA : Servicio Ocupado";
    } else {
        delete servidor->nextPendingConnection();
        qDebug()<<"SERVIDOR : Nuevo Cliente : Rechazado (Servicio Ocupado)";
    }
}

void Sesion::despacharCliente()
{
    cliente->~QTcpSocket();
    qDebug()<<"SERVIDOR : Cliente : Desconectado";
    servicioOcupado = false;
    qDebug()<<"TERMINAL REMOTA : Servicio Disponible";
}

void Sesion::leerStdout()
{
    cliente->write(comando->readAllStandardOutput());
}

void Sesion::leerError()
{
    cliente->write(comando->readAllStandardError());
}

void Sesion::leerStdin()
{
    QString cmd = cliente->readAll();
    comando->start(cmd);
}
