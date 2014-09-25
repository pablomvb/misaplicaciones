#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <camara.h>

class socket : public QObject
{
    Q_OBJECT
    Camara* webCam;

    QTcpServer* server;
    QTcpSocket* cliente;

    bool conexionActiva;

public:
    explicit socket(QObject *parent = 0);

signals:
    void transmision(bool estado, QString ip, int port);

public slots:

private slots:
    void nuevaConexion();
    void cmdin();
    void desconectar();

};

#endif // SOCKET_H
