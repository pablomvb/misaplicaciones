#include "downmanager.h"

DownManager::DownManager(QObject *parent) :
    QObject(parent)
{
}

void DownManager::downFile(QString urlFile)
{
    url = urlFile;
    data.clear();
    reply = qnam.get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this,SLOT(finDownFile()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(leerDownFile()));
}

void DownManager::finDownFile()
{
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(reply->error()){
        data.clear();
        emit estado(-1);
    } else if(!redirectionTarget.isNull()){
        QUrl newUrlDirection = url.resolved(redirectionTarget.toUrl());
        urlRedirection = newUrlDirection.toString();
        emit estado(1);
        downFile(urlRedirection);
    }
    else{
        emit estado(0);
    }
    disconnect(reply,SIGNAL(finished()),this,SLOT(finDownFile()));
    disconnect(reply,SIGNAL(readyRead()),this,SLOT(leerDownFile()));
    reply = 0;
}

void DownManager::leerDownFile()
{
    data.append(reply->readAll());
}
