#ifndef APPTHREAD_H
#define APPTHREAD_H

#include <QThread>
#include <QProcess>
#include <QDebug>

class AppThread : public QThread
{
    Q_OBJECT
    bool bucle;
    bool runStop;
    QString nameApp;
    QString cmdApp;
    QStringList argApp;
    QProcess *aplicacion;


public:
    explicit AppThread(QString nameApp, QString cmdApp, bool bucle, QObject *parent = 0);
    void separarArgCmd();

public slots:
    void run();
    void stop();
    void error(int error);
    void removeApp();
    void cambioEstadoBucle(bool newEstado);
    void resetApp();
    void forceStop();
    void verificacion(QProcess::ProcessState estadoApp);

signals:
    void estadoProceso(int estado);
    void signalError(int errorE);
    void pid(QString pidCount);
};

#endif // APPTHREAD_H
