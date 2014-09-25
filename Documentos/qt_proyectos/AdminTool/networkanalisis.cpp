#include "networkanalisis.h"
#include "ui_networkanalisis.h"
#include <QFile>
#include "dialogmodo.h"
#include <QDebug>
#include <QNetworkAddressEntry>
#include <QNetworkInterface>
#include "dialogseleciface.h"

networkAnalisis::networkAnalisis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::networkAnalisis)
{
    ui->setupUi(this);
    cmdPing = new QProcess(this);
    connect(cmdPing,SIGNAL(readChannelFinished()),this,SLOT(pingIpPasoDos()));
    socketEscaner = new QTcpSocket(this);
    showNormal();
    ui->progressBar->setValue(0);
    barra = 0;
}

networkAnalisis::~networkAnalisis()
{
    delete ui;
}

int networkAnalisis::cargarConfiguracion()
{
    QFile fileConfig;
    int m;
    fileConfig.setFileName("config.f");
    QString data;
    if(fileConfig.open(QIODevice::ReadOnly)){
        data = fileConfig.readAll();
        if(data.contains("lan")){
            m = 1;
        }
        else{
            if(data.contains("localhost")){
                m = 2;
            }
        }
    }
    else{
        DialogModo modoSelecion;
        if(modoSelecion.exec()==QDialog::Accepted){
            m = modoSelecion.getModo();
            fileConfig.open(QIODevice::WriteOnly);
            switch (m) {
            case 1:
                data = "lan";
                break;
            case 2:
                data = "localhost";
                break;
            }
            fileConfig.write(data.toLatin1());
            fileConfig.waitForBytesWritten(0);
        }
        else{
            emit exitProgram();
            exit(0);
            return 0;
        }
    }
    fileConfig.close();
    qDebug()<<"file_config: "<<data;
    return m;
}

void networkAnalisis::initScan()
{
    modo = cargarConfiguracion();
    probarIps.clear();
    contador = 0;
    switch (modo) {
    case 1:
        if(obtenerIpLocal()==1){
            QStringList a = infoNetwork.split("|");
            QStringList ipBase = a.value(2).split(".");
            QString base = ipBase.value(0)+"."+ipBase.value(1)+"."+ipBase.value(2)+".";
            for(int i=1; i<256;i++){
                if(a.value(3).toInt()!=i){
                    probarIps.append(base+QString().setNum(i));
                }
            }
        }
        else{
            emit exitProgram();
            exit(0);
        }
        break;
    case 2:
        probarIps<<"localhost";
        break;
    }
    qDebug()<<infoNetwork;
    qDebug()<<probarIps;
    pingIp();
}

void networkAnalisis::conectarAdminTool()
{
    for(int i=0; i<IpsValidas.count();i++){
        socketEscaner->connectToHost(IpsValidas.value(0),6900);
        if(socketEscaner->waitForConnected(20)){
            QString dataSend = "1005|OK_ADMINTOOL";
            socketEscaner->write(dataSend.toLatin1());
            socketEscaner->waitForBytesWritten(0);
            socketEscaner->disconnectFromHost();
        }
    }
}

void networkAnalisis::pingIp()
{
    QString comando = "ping";
    QStringList arg;
#ifdef linux
    arg<<probarIps.value(contador);
    arg<<"-c 2";
#endif

#ifdef _WIN32
    arg<<probarIps.value(contador);
#endif
    qDebug()<<comando<<arg;
    cmdPing->start(comando,arg);
    if(probarIps.count()==1){
        ui->progressBar->setValue(80);
    }
    else{
        if(probarIps.count()>0){
            ui->progressBar->setValue(ui->progressBar->value()+barra);
        }
    }
}

void networkAnalisis::pingIpPasoDos()
{
    QString data = cmdPing->readAll();
    QStringList d = data.split("\n");
#ifdef linux
    for(int i=0; i<d.count(); i++){
        if(d.value(i).contains("received")){
            data.clear();
            data = d.value(i);
            i = d.count();
        }
    }
    qDebug()<<data;
    d.clear();
    d = data.split(",");
    data.clear();
    data = d.value(1);
    qDebug()<<data;
    d.clear();
    d = data.split(" ");
    data.clear();
    data = d.value(1);
#endif

    if(data.toInt()>0){
        IpsValidas.append(probarIps.value(0));
        socketEscaner->connectToHost(probarIps.value(0),6900);
        if(socketEscaner->waitForConnected(20)){
            QString dataSend = "1005|OK_ADMINTOOL";
            QStringList a = infoNetwork.split("|");
            switch (modo) {
            case 1:
                dataSend.append("|");
                dataSend.append(a.value(2));
                break;
            case 2:
                dataSend.append("|localhost");
                break;
            }
            qDebug()<<dataSend;
            socketEscaner->write(dataSend.toLatin1());
            socketEscaner->waitForBytesWritten(0);
            socketEscaner->disconnectFromHost();
        }
    }
    probarIps.removeAt(0);
    if(modo==1){
        if(probarIps.count()>0){
            pingIp();
        }
        else{
            if(probarIps.count()==0){
                close();
            }
        }
    }
    else{
        close();
    }
}

int networkAnalisis::obtenerIpLocal()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    QStringList data;
    for(int i=0; i < ifaces.count(); i++){
        QStringList a;
        a<<ifaces.value(i).humanReadableName();
        a<<ifaces.value(i).hardwareAddress();
        QList<QNetworkAddressEntry> ips = ifaces.value(i).addressEntries();
        if(ips.count()>0){
            for(int j=0; j<ips.count(); j++){
                if(ips.value(j).ip().toString().contains(".") && !ips.value(j).ip().toString().contains("127.0.0.1")){
                    a<<ips.value(j).ip().toString();
                }
            }
        }
        if(a.count()>2){
            data.append(a.value(0)+"|"+a.value(1)+"|"+a.value(2));
        }
    }

    if(data.count()>1){
        DialogSelecIface sIface;
        sIface.setDataIface(data);
        if(sIface.exec()==QDialog::Accepted){
            infoNetwork = sIface.getIfaceSelec();
        }
        else{
            emit exitProgram();
            exit(0);
            return 0;
        }
    }
    else{
        infoNetwork = data.value(0);
    }
    return 1;
}
