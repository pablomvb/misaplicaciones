#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "winforcionequipo.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    puertoLocal = 6901;
    ui->tableWidget->setColumnCount(1);
    tEspera = 5;
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(0,QHeaderView::Stretch);
    header->setVisible(false);
    QStringList nameLabels;
    nameLabels<<"Equipos";
    ui->tableWidget->setHorizontalHeaderLabels(nameLabels);
    escaner = new networkAnalisis();
    escaner->show();
    escaner->initScan();
    connect(ui->btnEscanear,SIGNAL(clicked()),this,SLOT(clickEscanear()));
    showNormal();
    servidor = new QTcpServer(this);
    connect(servidor,SIGNAL(newConnection()),this,SLOT(newEquipo()));
    servidor->listen(QHostAddress::Any,puertoLocal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newEquipo(QString ipRemota)
{
    socketServicio = new QTcpSocket(this);
    socketServicio->connectToHost(ipRemota,puertoLocal);
    if(socketServicio->waitForConnected(tEspera)){
        connect(socketServicio,SIGNAL(readyRead()),this,SLOT(shellServicio()));
        QString data;
        data.append("1001|AdminTool");
        socketServicio->write(data.toLatin1());
    }
    else{
        socketServicio->~QTcpSocket();
    }
}

void MainWindow::newEquipo()
{
    wInforcionEquipo* item = new wInforcionEquipo();
    item->setSocketPrt(servidor->nextPendingConnection());
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,0,item);
    ui->tableWidget->setRowHeight(ui->tableWidget->rowCount()-1,45);
}

void MainWindow::clickEscanear()
{

}
