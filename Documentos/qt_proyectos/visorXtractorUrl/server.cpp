#include "server.h"
#include <QListWidget>

server::server(QObject *parent) :
    QObject(parent)
{
    serverSocket = new QTcpServer(this);
}

void server::run()
{
    if(serverSocket->listen(QHostAddress::Any,6509)){
        connect(serverSocket,SIGNAL(newConnection()),this,SLOT(newConection()));
    }
    else{
        exit(-1);
    }
}

void server::read()
{
    QString label = inputVisor->readAll();
    QStringList dataBuffer = label.split("\n");
    for (int var = 0; var < dataBuffer.count(); var++) {
        emit data(dataBuffer.value(var));
    }
}

void server::newConection()
{
    inputVisor = serverSocket->nextPendingConnection();
    serverSocket->pauseAccepting();
    emit clear();
    connect(inputVisor,SIGNAL(readyRead()),this,SLOT(read()));
    connect(inputVisor,SIGNAL(disconnected()),this,SLOT(lostConection()));
}

void server::lostConection()
{
    disconnect(inputVisor,SIGNAL(readyRead()),this,SLOT(read()));
    disconnect(inputVisor,SIGNAL(disconnected()),this,SLOT(lostConection()));
    inputVisor->~QTcpSocket();
    inputVisor = 0;
    serverSocket->resumeAccepting();
}
