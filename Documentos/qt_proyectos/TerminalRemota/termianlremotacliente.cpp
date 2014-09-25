#include "termianlremotacliente.h"
#include "ui_termianlremotacliente.h"

TermianlRemotaCliente::TermianlRemotaCliente(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TermianlRemotaCliente)
{
    ui->setupUi(this);
    cliente = new QTcpSocket();
    ui->btnDesconectar->setEnabled(false);
    connect(ui->btnConectar,SIGNAL(clicked()),this,SLOT(conectarCliente()));
    connect(ui->btnDesconectar,SIGNAL(clicked()),this,SLOT(desconectarCliente()));
    connect(ui->btnEnviar,SIGNAL(clicked()),this,SLOT(enviarComando()));
    connect(cliente,SIGNAL(readyRead()),this,SLOT(leerStdout()));
}

TermianlRemotaCliente::~TermianlRemotaCliente()
{
    delete ui;
}

void TermianlRemotaCliente::conectarCliente()
{
    cliente->connectToHost(ui->txtIpCliente->text(),6901);
    if(cliente->waitForConnected(5)){
        ui->btnConectar->setEnabled(false);
        ui->btnDesconectar->setEnabled(true);
        ui->listWidget->addItem("Conectado");
    }
    else{
        ui->listWidget->addItem("No se pudo establecer la conexion");
    }
}

void TermianlRemotaCliente::desconectarCliente()
{
    cliente->disconnect();
    ui->btnConectar->setEnabled(true);
    ui->btnDesconectar->setEnabled(false);
}

void TermianlRemotaCliente::enviarComando()
{
    cliente->write(ui->tctComando->text().toLatin1());
    cliente->waitForBytesWritten(2);
}

void TermianlRemotaCliente::leerStdout()
{
    ui->listWidget->addItem(QString(cliente->readAll()));
}
