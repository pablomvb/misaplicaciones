#ifndef APLICACION_H
#define APLICACION_H

#include <QThread>
#include <QProcess>

class aplicacion : public QThread
{
    Q_OBJECT
    QProcess* subproceso;
    bool persistencia;
    bool aplicacionIniciada;
    int retraso;
    QString estadoAplicacionThread;
    int pid;

enum BandejaNotificacion{AplicacionInciada, AplicacionTerminada, AplicacionReset, AplicacionError,IniciandoDaemon,Apagar,Bloquear,Reiniciar};

public:
    explicit aplicacion(QObject *parent = 0);
    void iniciar();
    void terminar();
    void matar();
    void setAplicacionComando(QString cmd, QStringList arg, bool persistencia,int r);
    QString getDatosAplicacion();
    int getTiempoRetraso(){ return pid;}

signals:
    void mensajeBandejaDeNotificacion(QString nombreAplicacion,QString informacion,int estado);
    void actualizar();

public slots:
    void estadoAplicacion(QProcess::ProcessState estadoAplicacion);
    void reiniciar(int codigoError,QProcess::ExitStatus codigoEstado);

};

#endif // APLICACION_H
