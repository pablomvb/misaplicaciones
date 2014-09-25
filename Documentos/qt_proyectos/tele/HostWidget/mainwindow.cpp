#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("wHost");
    modoRunning = 1;
    tiempoEsperaConeccion = 5;
    puertoLocal = 6900;
    lockHostConeccion = false;
    servidor = new QTcpServer(this);
    ui->wInfoControl->setVisible(false);
    sizeB.setWidth(width());
    sizeB.setHeight(height());
    sizeC.setHeight(height()+100);
    sizeC.setWidth(width()+200);
    connect(ui->wInfoControl,SIGNAL(disconecControl()),this,SLOT(disconecControl()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModoLoad(int modo)
{
    modoRunning = modo; // 0 pruebas en el host || 1 modo normal
}

void MainWindow::nuevaConeccion()
{
    if(lockHostConeccion == false && servidor->hasPendingConnections() == true){
        socketServicio = servidor->nextPendingConnection();
        qDebug()<<"Coneccion entrante";
        lockHostConeccion = true;
        connect(socketServicio,SIGNAL(readyRead()),this,SLOT(shellServicio()));
    }
}

void MainWindow::shellServicio()
{
    QString data = socketServicio->readAll();
    qDebug()<<"RAW:  "<<data;
    QStringList cmdArg = data.split("|");
    comando = cmdArg.value(0).toInt();
    switch (comando) {
    case 1005:
        disconnect(socketServicio,SIGNAL(readyRead()),this,SLOT(shellServicio()));
        if(cmdArg.value(1).contains("OK_ADMINTOOL")){
            ui->wInfoControl->setData(69001,ipLocal,nameMachine,oSmachine);
            if(ui->wInfoControl->contarAdminTool(cmdArg.value(2),6901)){
                resize(sizeC);
                ui->wInfoControl->setVisible(true);
            }
        }
        else{
            socketServicio->disconnectFromHost();
            socketServicio->~QTcpSocket();
            socketServicio = NULL;
            lockHostConeccion = false;
            nuevaConeccion();
        }
        break;
    }
}

void MainWindow::setNameMachine(QString name)
{
    nameMachine = name;
    ui->nameMachine->setText(nameMachine);
}

void MainWindow::setIpLocal(QString ip)
{
    ipLocal = ip;
    ui->ipLocal->setText(ipLocal);
}

void MainWindow::disconecControl()
{
    resize(sizeB);
    lockHostConeccion = false;
}

void MainWindow::setup()
{
    switch (modoRunning) {
    case 0:
        setIpLocal("localhost");
        break;
    default:
        break;
    }
    QStringList list;

    #ifdef linux
        list = QProcess::systemEnvironment().filter("USER=");
        oSmachine = "linux";
    #endif

    #ifdef _WIN32
        list = QProcess::systemEnvironment().filter("USERNAME=");
        oSmachine = "windows";
    #endif

    QString userName = list.value(0);

    #ifdef linux
        userName.remove(0,5);
    #endif

    #ifdef _WIN32
        userName.remove(0,9);
    #endif

    setNameMachine(userName);

    if(!servidor->listen(QHostAddress::Any,puertoLocal)){
        qDebug()<<"Imposible iniciar el servidor";
        exit(0);
    }

    connect(servidor,SIGNAL(newConnection()),this,SLOT(nuevaConeccion()));
}
