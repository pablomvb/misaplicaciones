#include "socket.h"
#include <QMessageBox>
#include <QDebug>

socket::socket(QObject *parent) :
    QObject(parent)
{
    conexionActiva = false;
    webCam = new Camara();
    server = new QTcpServer();
    connect(server,SIGNAL(newConnection()),this,SLOT(nuevaConexion()));
    if(!server->listen(QHostAddress::Any,6590)){
        QMessageBox msj;
        msj.setInformativeText("No se pudo iniciar el servidor");
        msj.exec();
        exit(0);
    }
    webCam->stream();
}

void socket::nuevaConexion()
{
    if(!conexionActiva){
        qDebug()<<"Conexion: ENTRADA: aceptada";
        cliente = server->nextPendingConnection();
        conexionActiva = true;
        connect(cliente,SIGNAL(readyRead()),this,SLOT(cmdin()));
        connect(cliente,SIGNAL(disconnected()),this,SLOT(desconectar()));
    }
    else{
        qDebug()<<"Conexion: ENTRADA: rachazada";
        delete server->nextPendingConnection();
    }
}

void socket::cmdin()
{
    QStringList buffer = QString(cliente->readAll()).split("\n");

    QStringList cmd;

    for(int contador = 0; contador<buffer.count(); contador++){
        cmd.clear();
        if(buffer.value(contador).count()>0){
            cmd = buffer.value(contador).split("|*|");
            qDebug()<<cmd;
            switch (cmd.value(0).toInt()) {
            case 1:
                if(cmd.value(1).contains("INICIAR")){
                    webCam->iniciarCaptura(QHostAddress("localhost"),6591);
                }else if(cmd.value(1).contains("DETENER")){
                    webCam->detenerCaptura();
                }
                break;
            default:
                break;
            }
        }
    }
}

void socket::desconectar()
{
    conexionActiva = false;
    disconnect(cliente,SIGNAL(readyRead()),this,SLOT(cmdin()));
    disconnect(cliente,SIGNAL(disconnected()),this,SLOT(desconectar()));
    qDebug()<<"Cliente desconectado";
}

































