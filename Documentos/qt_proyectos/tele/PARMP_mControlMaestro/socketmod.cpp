#include "socketmod.h"
#include <QDebug>

socketMod::socketMod(QString ip, int port, QObject *parent) :
    QTcpSocket(parent)
{
    ipRemota.setAddress(ip);
    portRemoto = port;
    connectToHost(ipRemota,portRemoto);
    connect(this,SIGNAL(readyRead()),this,SLOT(shell()));
}

void socketMod::setIpRemota(QString ip)
{
    ipRemota.setAddress(ip);
}

void socketMod::shell()
{
    qDebug()<<"comando recivido";
    QString data;
    data.append(readAll());
    QStringList comandoArg = data.split("|");
    qDebug()<<comandoArg;

    comando = comandoArg.value(0).toInt();

    switch (comando) {
    case 102:
        ipRemota.setAddress(comandoArg.value(1));
        nombreEquipo = comandoArg.value(2);
        break;
    }
}

void socketMod::iniciar()
{
    qDebug()<<"init comunicacion";
    QString cmd;
    cmd.setNum(101);
    write(cmd.toLatin1());
    waitForBytesWritten(0);
}
