#include "winforcionequipo.h"
#include "ui_winforcionequipo.h"
#include <QDebug>

wInforcionEquipo::wInforcionEquipo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wInforcionEquipo)
{
    ui->setupUi(this);
}

wInforcionEquipo::~wInforcionEquipo()
{
    delete ui;
}

void wInforcionEquipo::setBasicData(QString ip, int port, QString oS, QString nameMachine)
{
    rIp = ip;
    rPort = port;
    rOs = oS;
    rNameMachine = nameMachine;
}

void wInforcionEquipo::setSocketPrt(QTcpSocket *prt)
{
    socketControl = prt;
    connect(socketControl,SIGNAL(readyRead()),this,SLOT(shell()));
}

void wInforcionEquipo::updateLabel()
{
    ui->vIpEquipo->setText(rIp);
    ui->vNombreEquipo->setText(rNameMachine);
}

void wInforcionEquipo::shell()
{
    QString dataR = socketControl->readAll();
    QStringList d = dataR.split("|");
    int comando = d.value(0).toInt();
    switch (comando) {
    case 1010:
        QStringList f = d.value(1).split(";");
        qDebug()<<f;
        setBasicData(f.value(0),6901,f.value(2),f.value(1));
        updateLabel();
        break;
    }
}
