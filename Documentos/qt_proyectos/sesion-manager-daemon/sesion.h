#ifndef SESION_H
#define SESION_H

#include <QObject>
#include <aplicacion.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class Sesion : public QObject
{
    Q_OBJECT
    QList<aplicacion *> listaAplicaciones;

    QTcpServer *servidor;
    QTcpSocket *cliente;
    bool clienteConectado;

    void iniciarServidor();

enum BandejaNotificacion{AplicacionInciada, AplicacionTerminada, AplicacionReset, AplicacionError,IniciandoDaemon,Apagar,Bloquear,Reiniciar};
public:
    explicit Sesion(QObject *parent = 0);
    void loadListaAplicaciones();

signals:

public slots:
    void nuevoCliente();
    void desconectarCliente();
    void writeDatos(QByteArray datos);
    void shell();
    void nuevaNotificacion(QString apliacion,QString informacion,int estado);
    void comando_nuevaApliacion(QStringList aplicacionCmdArg);
    void comando_actualizarCliente();
    void conectarAplicacionBandeja(aplicacion *ptrAplicacion);
    void desconectarAplicacionBandeja(aplicacion *ptrAplicacion);
};

#endif // SESION_H
