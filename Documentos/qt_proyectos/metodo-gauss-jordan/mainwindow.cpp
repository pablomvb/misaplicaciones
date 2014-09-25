#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    math = new matematicaString();
    connect(ui->btnSend,SIGNAL(clicked()),this,SLOT(shell()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::shell()
{
    QStringList cmd;
    QStringList salida;
    cmd = ui->txtCmd->text().split(" ");
    if(cmd.count()>1){
        output(ui->txtCmd->text());
        ui->txtCmd->setText("espere ... procesando ...");
        ui->txtCmd->setEnabled(false);
        ui->btnSend->setEnabled(false);

        if(cmd.value(0).contains("dividirE")==true){
            QStringList arg;
            arg = cmd.value(1).split(";");
            salida<<QString("\tCociente: ")+math->dividirEntero(arg.value(0),arg.value(1),COCIENTE);
            salida<<QString("\tModulo: ")+math->dividirEntero(arg.value(0),arg.value(1),MODULO);
        }

        if(cmd.value(0).contains("dividirF")==true){
            QStringList arg;
            arg = cmd.value(1).split(";");
            salida<<QString("\tCociente: ")+math->dividirFlotante(arg.value(0),arg.value(1),COCIENTE);
            salida<<QString("\tModulo: ")+math->dividirFlotante(arg.value(0),arg.value(1),MODULO);
        }

        if(cmd.value(0).contains("getPrecision")==true){
            salida<<"Precision = "+QString().setNum(math->getPrecision());
        }

        if(cmd.value(0).contains("setPrecision")==true){
            math->setPrecision(cmd.value(1).toInt());
            salida<<"Precision = "+QString().setNum(math->getPrecision());
        }

        ui->txtCmd->setText("");
        ui->txtCmd->setEnabled(true);
        ui->btnSend->setEnabled(true);
    }
    else{
        salida<<"Error: "+ui->txtCmd->text()+" ; comando reconocido";
    }

    output(salida);
}

void MainWindow::output(QString stdOut)
{
    ui->listOutput->addItem(stdOut);
    ui->listOutput->scrollToBottom();
}

void MainWindow::output(QStringList stdOut)
{
    ui->listOutput->addItems(stdOut);
    ui->listOutput->scrollToBottom();
}
