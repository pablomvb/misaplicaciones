#ifndef SESION_H
#define SESION_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
//  #include "comando.h"
#include <QProcess>
#include <QThread>

class Sesion : public QObject
{
    Q_OBJECT

    QThread* hilo;
    QProcess* comando;

    QTcpServer* servidor;
    QTcpSocket* cliente;
    bool servicioOcupado;

public:
    explicit Sesion(QObject *parent = 0);
    void iniciarServicio();
    void iniciarServidor();

signals:

public slots:
    void nuevoCliente();
    void despacharCliente();
    void leerStdout();
    void leerError();
    void leerStdin();

};

#endif // SESION_H
