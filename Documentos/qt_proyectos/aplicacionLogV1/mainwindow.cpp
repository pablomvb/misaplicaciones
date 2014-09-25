#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    app = new QProcess(this);
    connect(app,SIGNAL(readyReadStandardError()),this,SLOT(leerStdOut()));
    connect(app,SIGNAL(readyReadStandardOutput()),this,SLOT(leerStdOutA()));
    //setStyleSheet("background-image: url(/home/ninbus/Descargas/usb_pic/1491258_10154074270110088_3189235656499035987_o.jpg)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::leerStdOut()
{
    //qDebug()<<"senhal recivida";
    ui->listWidget->addItem(app->readAllStandardError());
    ui->listWidget->scrollToBottom();
}

void MainWindow::leerStdOutA()
{
    QStringList out;
    out<<app->readAllStandardOutput();
    qDebug()<<out;
    ui->listWidget->addItems(out);
    ui->listWidget->scrollToBottom();
}

void MainWindow::iniciarApp()
{
    QString nApp;
    nApp = ui->lineEdit->text();
    //nApp = "/home/ninbus/qt_proyectos/build-ConversorGUI2-Desktop_Qt_5_2_0_qt5-Debug/ConversorGUI2";
    app->start(nApp);
}
