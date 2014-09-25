#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <networkanalisis.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpSocket* socketServicio;
    QTcpServer* servidor;
    networkAnalisis* escaner;
    QString ipLocal;
    int puertoLocal;
    int tEspera;

private:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newEquipo(QString ipRemota);
    void newEquipo();
    void clickEscanear();

};

#endif // MAINWINDOW_H
