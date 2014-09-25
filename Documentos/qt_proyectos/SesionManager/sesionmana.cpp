#include "sesionmana.h"
#include "ui_sesionmana.h"
#include <QMessageBox>
#include <QHostAddress>

SesionMana::SesionMana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SesionMana)
{
    ui->setupUi(this);
    setWindowTitle("Control de Sesion");
    ui->widget->setVisible(false);

    loadHeaderTable();

    cliente = new QTcpSocket();
    connect(cliente,SIGNAL(disconnected()),this,SLOT(clienteDesconectado()));
    connect(cliente,SIGNAL(readyRead()),this,SLOT(shell()));
    cliente->connectToHost(QHostAddress::LocalHost,6001);
    if(!cliente->waitForConnected(5)){
        clienteDesconectado();
    }
    connect(ui->pushButton,SIGNAL(clicked()),ui->widget,SLOT(nuevaAplicacion()));
    connect(ui->widget,SIGNAL(getDatosAplicacion(QByteArray)),this,SLOT(enviarDatos(QByteArray)));
    actualizarTabla();
}

void SesionMana::actualizarTabla()
{
    enviarDatos(QString("-1").toLatin1());
}

void SesionMana::loadHeaderTable()
{
    QStringList nameLabels;
    nameLabels<<"Item"<<"PID"<<"Estatus";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(nameLabels);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setVisible(true);
    header->setSectionResizeMode(0,QHeaderView::Stretch);
    header->setSectionResizeMode(1,QHeaderView::Fixed);
    header->setSectionResizeMode(2,QHeaderView::Fixed);
}

SesionMana::~SesionMana()
{
    delete ui;
}

void SesionMana::clienteDesconectado()
{
    QMessageBox msjError;
    msjError.setWindowTitle("Error");
    msjError.setInformativeText("Imposible comunicarse con el daemon");
    msjError.exec();
    exit(0);
}

void SesionMana::enviarDatos(QByteArray datos)
{
    cliente->write(datos);
    cliente->waitForBytesWritten(0);
}

void SesionMana::shell()
{
    QStringList datos = QString(cliente->readAll()).split("\n");
    int comando = datos.value(0).toInt();
    datos.removeFirst();
    switch (comando) {
    case 0:
        newDatosTabla(datos);
    break;
    }
}

void SesionMana::newDatosTabla(QStringList listaAplicaciones)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadHeaderTable();

    for (int var = 0; var < listaAplicaciones.count(); ++var) {
        if(listaAplicaciones.value(var).count()>0){
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            QStringList d = listaAplicaciones.value(var).split("//");
            qDebug()<<d;
            QTableWidgetItem* item0 = new QTableWidgetItem(d.value(0));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,item0);
            QTableWidgetItem* item1 = new QTableWidgetItem(d.value(1));
            item1->setFlags(Qt::ItemIsEditable);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,item1);
            QTableWidgetItem* item2 = new QTableWidgetItem();
            if(d.value(2).contains("Iniciado") || d.value(2).contains("ejecucion")){
                item2->setText("Corriendo");
                item2->setBackgroundColor(QColor("green"));
            }
            item2->setFlags(Qt::ItemIsEditable);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,item2);
        }
    }
}


























































