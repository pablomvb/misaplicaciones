#include "downmanager.h"
#include <QLabel>

DownManager::DownManager(QObject *parent) :
    QObject(parent)
{
    estado = 0;
    //signal = new SignalWait(this,SIGNAL(fDown()));
    connect(this,SIGNAL(iniciarDescargar()),this,SLOT(downDataUrl()));
}

int DownManager::urlDownload(QString url, int timeSeg)
{
    qDebug()<<"Descarga iniciada : "<<url;
    barDownload = new QProgressBar();
    barDownload->setWindowTitle("Progreso");
    barDownload->show();
    urlDireccion = url;
    emit iniciarDescargar();
    SignalWait signal(this,SIGNAL(fDown()));
    bool terminar = false;
    timeSeg = timeSeg*1000;
    do{
        if(signal.Wait(timeSeg)){
            if(estado==1 || estado==-1){
                terminar = true;
            }
        }
        else{
            terminar = true;
            estado = -1;
        }
    }while(!terminar);
    qDebug()<<"Desgarga terminada";
    barDownload->close();
    delete barDownload;
    return estado;
}

void DownManager::downDataUrl()
{
    data.clear();
    reply = qnam.get(QNetworkRequest(urlDireccion));
    //qDebug()<<"Url conectada";
    connect(reply,SIGNAL(finished()),this,SLOT(finDownFile()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(leerDownFile()));
    connect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateProgressBar(qint64,qint64)));
}

void DownManager::updateProgressBar(qint64 d1, qint64 d2)
{
    barDownload->setMaximum(d2);
    barDownload->setValue(d1);
    //emit out(d1,d2);
}

void DownManager::finDownFile()
{
    disconnect(reply,SIGNAL(finished()),this,SLOT(finDownFile()));
    disconnect(reply,SIGNAL(readyRead()),this,SLOT(leerDownFile()));
    disconnect(reply,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateProgressBar(qint64,qint64)));
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(reply->error()){
        estado = -1;
        //qDebug()<<"D_ERROR";
        emit fDown();
    } else if(!redirectionTarget.isNull()){
        urlDireccion = urlDireccion.resolved(redirectionTarget.toUrl());
        reply->~QNetworkReply();
        reply = 0;
        estado = 2;
        //qDebug()<<"D_REDIRECCION";
        emit iniciarDescargar();
    }
    else{
        reply->~QNetworkReply();
        reply = 0;
        estado = 1;
        //qDebug()<<"D_OK , Size = "<<data.count();
        emit fDown();
    }
}

void DownManager::leerDownFile()
{
    data.append(reply->readAll());
    //qDebug()<<"Datos almacenados";
}
