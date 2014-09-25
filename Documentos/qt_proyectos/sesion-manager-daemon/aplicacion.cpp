#include "aplicacion.h"
#include <QDebug>

aplicacion::aplicacion(QObject *parent) :
    QThread(parent)
{
    subproceso = new QProcess();
    aplicacionIniciada = false;
    persistencia = false;

    connect(subproceso,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(estadoAplicacion(QProcess::ProcessState)));
    connect(subproceso,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(reiniciar(int,QProcess::ExitStatus)));
}

void aplicacion::iniciar()
{
    subproceso->start();
    qDebug()<<objectName()<<" _iniciado, pid = "<<subproceso->processId();
    emit mensajeBandejaDeNotificacion(objectName(),"",AplicacionInciada);
    aplicacionIniciada = true;
}

void aplicacion::reiniciar(int codigoError, QProcess::ExitStatus codigoEstado)
{
    if(codigoEstado==QProcess::NormalExit){
        qDebug()<<objectName()<<" _terminado";
        emit mensajeBandejaDeNotificacion(objectName(),"",AplicacionTerminada);
    }else if(codigoEstado==QProcess::CrashExit){
        qDebug()<<objectName()<<" _error, codigo = "<<codigoError;
        emit mensajeBandejaDeNotificacion(objectName(),"",AplicacionError);
    }

    if(persistencia){
        subproceso->start();
        qDebug()<<objectName()<<" _reiniciando";
        emit mensajeBandejaDeNotificacion(objectName(),"",AplicacionReset);
    }
}

void aplicacion::terminar()
{
    subproceso->terminate();
    aplicacionIniciada = false;
}

void aplicacion::matar()
{
    subproceso->kill();
    aplicacionIniciada = false;
}

void aplicacion::setAplicacionComando(QString cmd, QStringList arg, bool persistencia, int r)
{
    subproceso->setProgram(cmd);
    subproceso->setArguments(arg);
    this->persistencia = persistencia;
    retraso = r;
    pid = subproceso->processId();
    estadoAplicacionThread = "Sin iniciar";
}

QString aplicacion::getDatosAplicacion()
{
    QStringList retorno;
    retorno<< objectName();
    QString pidEstado;
    pidEstado.setNum(pid);
    retorno<<pidEstado;
    retorno<<estadoAplicacionThread;
    return retorno.join("//");
}

void aplicacion::estadoAplicacion(QProcess::ProcessState estadoAplicacion)
{
    switch (estadoAplicacion) {
    case QProcess::Starting:
        //qDebug()<<objectName()<<" iniciado";
        estadoAplicacionThread = "Iniciado";
        pid = subproceso->processId();
        break;
    case QProcess::Running:
        qDebug()<<objectName()<<" _corriendo";
        estadoAplicacionThread = "En ejecucion";
        pid = subproceso->processId();
        break;
    case QProcess::NotRunning:
        //qDebug()<<objectName()<<" terminado";
        estadoAplicacionThread = "Terminado";
        pid = subproceso->processId();
        break;
    }
    emit actualizar();
}
