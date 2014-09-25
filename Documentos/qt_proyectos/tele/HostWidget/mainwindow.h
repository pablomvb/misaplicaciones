#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include "widgetcontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QTcpServer* servidor;
    QTcpSocket* socketServicio;
    int modoRunning;
    int tiempoEsperaConeccion;
    QString ipLocal;
    QString nameMachine;
    QString oSmachine;
    int puertoLocal;
    bool lockHostConeccion;
    int comando;
    QSize sizeB;
    QSize sizeC;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setModoLoad(int modo);
    void setup();

private slots:
    void nuevaConeccion();
    void shellServicio();
    void setNameMachine(QString name);
    void setIpLocal(QString ip);
    void disconecControl();

};

#endif // MAINWINDOW_H
