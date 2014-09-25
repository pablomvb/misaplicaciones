#include "dnewapp.h"
#include "ui_dnewapp.h"
#include <QMessageBox>

dNewApp::dNewApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dNewApp)
{
    ui->setupUi(this);
    ui->label->setText("");
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),ui->label,SLOT(setText(QString)));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(btnOk()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
    ui->spinBox->setMaximum(3600);
}

dNewApp::~dNewApp()
{
    delete ui;
}

void dNewApp::btnOk()
{
    if(ui->lineEdit->text().size() == 0  || ui->lineEdit_2->text().size() == 0){
        QMessageBox *msj = new QMessageBox();
        msj->setText("Error, complete correctamente los casilleros.");
        msj->setIcon(QMessageBox::Critical);
        msj->show();
    }
    else{
        emit this->getData(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->spinBox->value(),ui->checkBox->isChecked());
        this->close();
    }
}

void dNewApp::cleanData()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->spinBox->setValue(0);
    ui->checkBox->setChecked(false);
}

void dNewApp::setData(QString nameApp, QString cmdApp, int time, bool persistencia)
{
    ui->lineEdit->setText(nameApp);
    ui->lineEdit_2->setText(cmdApp);
    ui->spinBox->setValue(time);
    ui->checkBox->setChecked(persistencia);
}
