#include "widgetcontrol.h"
#include "ui_widgetcontrol.h"

widgetControl::widgetControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetControl)
{
    ui->setupUi(this);
    setWindowTitle("CSesion");
}

widgetControl::~widgetControl()
{
    delete ui;
}
void widgetControl::startControl()
{

}

void widgetControl::stopControl()
{

}

void widgetControl::setData(int puerto, QString ip, QString name, QString oS)
{
    ipLocal = ip;
    puertoLocal = puerto;
    this->oS = oS;
    nameMachine = name;
}

bool widgetControl::contarAdminTool(QString ip, int port)
{
    socketControl = new QTcpSocket(this);
    ipR = ip;
    puertoR = port;
    connect(socketControl,SIGNAL(readyRead()),this,SLOT(shellControl()));
    connect(socketControl,SIGNAL(disconnected()),this,SLOT(clear()));
    socketControl->connectToHost(ip,port);
    if(socketControl->waitForConnected(10)){
        ui->wInfoAmin->setEstado(2);
        QString dataSend;
        dataSend.append("1010|");
        dataSend.append(ipLocal+";");
        dataSend.append(nameMachine+";");
        dataSend.append(oS);
        socketControl->write(dataSend.toLatin1());
        socketControl->waitForBytesWritten(0);
        return true;
    }
    return false;
}

void widgetControl::shellControl()
{
    QString dataRAW = socketControl->readAll();
    qDebug()<<"RAW_control :"<<dataRAW;
    QStringList data = dataRAW.split("|");
    comando = data.value(0).toInt();
    switch (comando) {
    case 1007:
        if(data.value(1).contains("OK_WIDGET")){

        }
        break;
    }
}

void widgetControl::clear()
{
    ui->wInfoAmin->setEstado(0);
    disconnect(socketControl,SIGNAL(readyRead()),this,SLOT(shellControl()));
    disconnect(socketControl,SIGNAL(disconnected()),this,SLOT(clear()));
    socketControl->~QTcpSocket();
    setVisible(false);
    emit disconecControl();
}
