#include "appthread.h"

AppThread::AppThread(QString nameApp, QString cmdApp, bool bucle, QObject *parent) :
    QThread(parent)
{
    this->nameApp = nameApp;
    this->cmdApp = cmdApp;
    this->bucle = bucle;

    this->separarArgCmd();

    this->aplicacion = new QProcess(this);
    this->aplicacion->setArguments(this->argApp);
    this->aplicacion->setProgram(this->cmdApp);

    connect(this->aplicacion,SIGNAL(finished(int)),this,SLOT(error(int)));
    connect(this->aplicacion,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(verificacion(QProcess::ProcessState)));
}

void AppThread::separarArgCmd()
{
    QString palabra;
    QString cmd = this->cmdApp;
    this->cmdApp.clear();
    if(cmd.at(0)==' '){
        cmd.remove(0,1);
    }
    do{
        if(cmd.at(0)==' '){
            this->argApp << palabra;
            palabra.clear();
            cmd.remove(0,1);
        }
        palabra.append(cmd.at(0));
        cmd.remove(0,1);
    }while(cmd.size() != 0);
    this->argApp << palabra;
    this->cmdApp = this->argApp.value(0);
    this->argApp.removeAt(0);
}

void AppThread::run()
{
    this->aplicacion->start();
    this->runStop = true;
    emit this->pid(QString().setNum(aplicacion->processId()));
    emit this->estadoProceso(1);
    qDebug()<<nameApp<<" : comando ejecutado";
}

void AppThread::stop()
{
    this->aplicacion->terminate();
    this->runStop = false;
    emit this->estadoProceso(2);
    qDebug()<<"stop";
}

void AppThread::error(int error)
{
    qDebug()<<"error";
    if(error != 0){
        emit this->signalError(error);
        emit this->estadoProceso(2);
    }
    else{
        emit this->estadoProceso(2);
        if(bucle == true && runStop == true){
            this->run();
        }
    }
}

void AppThread::removeApp()
{
    this->aplicacion->kill();
    this->aplicacion->close();
    this->~AppThread();
}

void AppThread::cambioEstadoBucle(bool newEstado)
{
    this->bucle = newEstado;
}

void AppThread::resetApp()
{
    this->aplicacion->kill();
}

void AppThread::forceStop()
{
    this->aplicacion->kill();
    this->runStop = false;
    emit this->estadoProceso(2);
    qDebug()<<"stop";
}

void AppThread::verificacion(QProcess::ProcessState estadoApp)
{
    switch (estadoApp) {
    case QProcess::Starting:
        qDebug()<<nameApp<<" lanzado";
        break;
    case QProcess::Running:
        qDebug()<<nameApp<<" corriendo";
        break;
    case QProcess::NotRunning:
        qDebug()<<nameApp<<" detenido";
        break;
    }
}
