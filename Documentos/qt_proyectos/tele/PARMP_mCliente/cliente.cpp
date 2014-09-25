#include "cliente.h"
#include "ui_cliente.h"
#include <QDebug>
#include <QProcess>
//#include <QMessageBox>
#include <QNetworkInterface>

Cliente::Cliente(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cliente)
{
    ui->setupUi(this);
    setWindowTitle("Host");
    setupCliente();
}

Cliente::~Cliente()
{
    delete ui;
}

void Cliente::setupCliente()
{
    //inicializando objetos
        camaraWeb = new Camara(this);
        servidorControl = new QTcpServer(this);
        portLocal=6900;

        if(!servidorControl->listen(QHostAddress::Any,portLocal)){
            ui->txtEquipo->setText("Error!");
            ui->txtIp->setText("Error!");
            ui->wEstacionControl->setEstado(3);
            ui->wFlujoDisplay->setEstado(3);
            ui->wFlujoMouse->setEstado(3);
            ui->wFlujoTeclado->setEstado(3);
        }
        else{

        connect(servidorControl,SIGNAL(newConnection()),this,SLOT(coneccionEntrante()));

    //obteniendo ip y nombre del equipo local
        QStringList list;

        #ifdef linux
            list = QProcess::systemEnvironment().filter("USER=");
        #endif

        #ifdef _WIN32
            list = QProcess::systemEnvironment().filter("USERNAME=");
        #endif

        QString userName = list.value(0);

        #ifdef linux
            userName.remove(0,5);
        #endif

        #ifdef _WIN32
            userName.remove(0,9);
        #endif

/*
        QList<QHostAddress> listaIps;
        listaIps = QNetworkInterface::allAddresses();
        for(int i=0; i<listaIps.count(); i++){
            if(listaIps.value(i).toString().contains("127")==true){
                listaIps.removeAt(i);
            }
            if(listaIps.value(i).toString().contains(":")==true){
                listaIps.removeAt(i);
            }
        }
        ipLocal = listaIps.value(0).toString();
*/
        ipLocal = "localhost";
    // cargando datos locales
        ui->txtEquipo->setText(userName);
        ui->txtIp->setText(ipLocal);
        ui->wEstacionControl->setEstado(0);
        ui->wFlujoDisplay->setEstado(0);
        ui->wFlujoMouse->setEstado(0);
        ui->wFlujoTeclado->setEstado(0);

        }
}

void Cliente::shell()
{
    qDebug()<<"comando recivido";
    QString data;
    data.append(socketControl->readAll());
    QStringList comandoArg;
    comandoArg = data.split("|");
    qDebug()<<comandoArg;

    comando = comandoArg.value(0).toInt();

    switch (comando) {
    case 101:
        QString dataSend;
        data.append(QString().setNum(1002));
        data.append("|");
        data.append(ipLocal);
        data.append("|");
        data.append(userName);
        socketControl->write(dataSend.toLatin1());
        socketControl->waitForBytesWritten(0);
        break;
    }
}

void Cliente::coneccionEntrante()
{
    socketControl = servidorControl->nextPendingConnection();
    ui->wEstacionControl->setEstado(2);
    //ui->wFlujoDisplay->setEstado(2);
    //ui->wFlujoMouse->setEstado(2);
    //ui->wFlujoTeclado->setEstado(2);
    connect(socketControl,SIGNAL(readyRead()),this,SLOT(shell()));
    connect(socketControl,SIGNAL(disconnected()),this,SLOT(clienteDesconectado()));
}

void Cliente::clienteDesconectado()
{
    ui->wEstacionControl->setEstado(0);
    disconnect(socketControl,SIGNAL(disconnected()),this,SLOT(clienteDesconectado()));
}


/*
 * desconetado 0
 * conectado   1
 * en espera   2
 * error       3
 *
 *
 *  comandos:
 *      199                indica que se recivio un comando desconocido
 *      101    retorna:    ip y nombre del host
 *      102                leer ip y nombre del host
 *      103                activa solo la visualizacion de la plantalla
 *      104                iniciar socketUDP display
 *      105                nuevoPuero control
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */







































