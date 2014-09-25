#include "controlmaestro.h"
#include "ui_controlmaestro.h"
#include <QNetworkInterface>

ControlMaestro::ControlMaestro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlMaestro)
{
    ui->setupUi(this);
    setWindowTitle("Asistente de Control");
    ui->btnModo->addItems(QStringList()<<"Control Remoto"<<"Visualizar Pantalla");
    //resolverIpLocal();
    //escanearRedLocal();
    anhadirItem("localhost");
    socketControl = new QTcpSocket(this);
    puertoControl = 6900;
    contadorPuertos = puertoControl +1;
    listarEquipos();
    connect(ui->btnEscanear,SIGNAL(clicked()),this,SLOT(escanearRedLocal()));
    connect(ui->btnModo,SIGNAL(activated(QString)),this,SLOT(debugModo(QString)));
}

ControlMaestro::~ControlMaestro()
{
    delete ui;
}

void ControlMaestro::eliminarItem()
{

}

void ControlMaestro::anhadirItem(QString ipEquipoRemoto)
{
    socketMod* newItem = new socketMod(ipEquipoRemoto,puertoControl,this);
    equipoLista.append(newItem);
    equipoLista.value(equipoLista.count()-1)->iniciar();
    qDebug()<<ipEquipoRemoto;
    qDebug()<<"num equipos: "<<equipoLista.count();
}

void ControlMaestro::escanearRedLocal()
{
    debugStatusBar("Escaneando red Local");
    QStringList iPbase = ipControlLocal.split(".");
    QString ipBaseCombinacion = iPbase.value(0) + "." + iPbase.value(1) + "." + iPbase.value(2) + ".";
    QStringList ipComprobar;
    for(int i=1; i<256;i++){
        if(iPbase.value(3).toInt() != i  && i != 0){
        //if(i != 0){
            ipComprobar<< ipBaseCombinacion + QString().setNum(i);
        }
    }
    //qDebug()<<"ips";
    for(int i=0; i<ipComprobar.count(); i++){
        //qDebug()<<i;
        QTcpSocket* sTest = new QTcpSocket(this);
        sTest->connectToHost(ipComprobar.value(i),puertoControl);
        if(sTest->waitForConnected(1)){
            anhadirItem(ipComprobar.value(i));
        }
        sTest->disconnectFromHost();
    }
    debugStatusBar("Escaneo finalizado");
    listarEquipos();
}

void ControlMaestro::debugModo(QString m)
{
    qDebug()<<m;
}

void ControlMaestro::debugStatusBar(QString addTxt)
{
    ui->statusBar->showMessage("iP: "+ipControlLocal+"   /   Realizando: "+addTxt);
}

void ControlMaestro::resolverIpLocal()
{
    debugStatusBar("Resolviendo ip local");
    QList<QHostAddress> lista = QNetworkInterface::allAddresses();
            for(int i=0; i<lista.count(); i++){
                if(lista.value(i).toString().contains("127")==true){
                    lista.removeAt(i);
                }
                if(lista.value(i).toString().contains(":")==true){
                    lista.removeAt(i);
                }
            }
    ipControlLocal = lista.value(0).toString();
    debugStatusBar("iP resuelta");
}

void ControlMaestro::listarEquipos()
{
    ui->listWidget->clear();
    for(int i=0; i<equipoLista.count(); i++){
        QString item;
        item.append(equipoLista.value(i)->getIp());
        item.append("  /  ");
        item.append(equipoLista.value(i)->getNombreEquipot());
        ui->listWidget->addItem(item);
    }
}

void ControlMaestro::testLocalHost()
{

}
