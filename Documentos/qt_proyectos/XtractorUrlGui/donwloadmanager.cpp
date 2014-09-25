#include "donwloadmanager.h"
#include "ui_donwloadmanager.h"

DonwloadManager::DonwloadManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DonwloadManager)
{
    ui->setupUi(this);
    setWindowTitle("Download Manager");
    estado = 0;
    //signal = new SignalWait(this,SIGNAL(fDown()));
    connect(this,SIGNAL(iniciarDescargar()),this,SLOT(downDataUrl()));
}

DonwloadManager::~DonwloadManager()
{
    delete ui;
}

int DonwloadManager::urlDownload(QString url, int timeSeg)
{
    qDebug()<<"Descarga iniciada : "<<url;
    ui->txtUrl->setText(url);
    ui->progressBar->setValue(0);
    ui->txtSize->setText(QString().setNum(dataRAW.count()));
    show();
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
    close();
    return estado;
}

void DonwloadManager::finDownFile()
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

void DonwloadManager::leerDownFile()
{
    dataRAW.append(reply->readAll());
    ui->txtSize->setText(QString().setNum(dataRAW.count()));
    //qDebug()<<"Datos almacenados";
}

void DonwloadManager::downDataUrl()
{
    dataRAW.clear();
    ui->txtUrl->setText(urlDireccion.toString());
    reply = qnam.get(QNetworkRequest(urlDireccion));
    //qDebug()<<"Url conectada";
    connect(reply,SIGNAL(finished()),this,SLOT(finDownFile()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(leerDownFile()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateProgressBar(qint64,qint64)));
}

void DonwloadManager::updateProgressBar(qint64 d1, qint64 d2)
{
    qDebug()<<d1<<"\t"<<d2;
    ui->progressBar->setMaximum(d2);
    ui->progressBar->setValue(d1);
}
