#include "mainwindow.h"
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QListWidget* list = new QListWidget();
    list->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
