#include "widgetselecionmetodo.h"
#include "ui_widgetselecionmetodo.h"

widgetSelecionMetodo::widgetSelecionMetodo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::widgetSelecionMetodo)
{
    ui->setupUi(this);
    ui->comboBox->addItems(QStringList()<<"FCFS"<<"SJF"<<"Basado en prioridades"<<"Round Robin"<<"Multicolas"<<"Multiprocesos");
    this->setWindowTitle("Metodo");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(selectMetodo()));
}

widgetSelecionMetodo::~widgetSelecionMetodo()
{
    delete ui;
}

void widgetSelecionMetodo::selectMetodo()
{
    //qDebug()<<ui->comboBox->currentText();
    emit this->getMetodo(ui->comboBox->currentText());
    this->close();
}
