#include "interfazapp.h"
#include <QCoreApplication>
#include <QDebug>
#include <cstring>

InterfazApp::InterfazApp(QObject *parent) :
    QObject(parent)
{
    appDownManager =new DownManager(this);
    connect(appDownManager,SIGNAL(estado(int)),this,SLOT(estadDownManager(int)));
    appCaptureUrl =  new Scaner(this);
    connect(appCaptureUrl,SIGNAL(estado(int)),this,SLOT(estadCaptureUrl(int)));
    subItemsMode = false;
}

void InterfazApp::start()
{
    urlDown = QCoreApplication::instance()->arguments().value(1);
    qDebug()<<"Analizar: "<<urlDown;
    appCaptureUrl->setIdScript(QUrl(urlDown).host());
    qDebug()<<"Etapa 1: ejecutando";
    appDownManager->downFile(urlDown);
}

void InterfazApp::startDownSubItems()
{
    qDebug()<<"Etapa 2: downSubItem["<<contadorSubItems+1<<"]";
    appDownManager->downFile(listaSubItems.value(contadorSubItems));
}

void InterfazApp::estadDownManager(int e)
{
    switch (e) {
    case -1:
        if(subItemsMode){
            qDebug()<<"downSubItem["<<contadorSubItems+1<<"] ... error";
        }
        else{
            qDebug()<<"Imposible acceder al sitio: "<<urlDown;
            qDebug()<<"Etapa 1: error";
        }
        exit(0);
        break;
    case 0:
        if(subItemsMode){
            listDataSubItems<<appDownManager->getData();
            contadorSubItems++;
            if(contadorSubItems < listaSubItems.count()){
                qDebug()<<"nextItem";
                startDownSubItems();
            }
            else{
                appCaptureUrl->setLisDataSubItems(listDataSubItems);
                qDebug()<<"initProcces";
                appCaptureUrl->startProcessSubItems();
            }
        }
        else{
            qDebug()<<"Etapa 1: OK";
            appCaptureUrl->setDataRAW(appDownManager->getData());
            if(appCaptureUrl->loadScript()==0){
                appCaptureUrl->createScript();
            }
        }
        break;
    case 1:
        qDebug()<<"Redireccionando: "<<appDownManager->getUrlRedirection();
        break;
    }
}

void InterfazApp::estadCaptureUrl(int e)
{
    switch (e) {
    case -1:
        qDebug()<<"Etapa 2: error";
        exit(0);
        break;
    case 0:
        qDebug()<<"Etapa 2: OK";
        //qDebug()<<"DATA_RAW:\n"<<appDownManager->getData();
        connect(appCaptureUrl,SIGNAL(estado(int)),this,SLOT(estadCaptureUrl(int)));
        appCaptureUrl->setDataRAW(appDownManager->getData());
        if(appCaptureUrl->loadScript()==0){
            appCaptureUrl->createScript();
        }
        break;
    case 1:
        qDebug()<<"Etapa 2: Descargando datos de los subItems";
        listaSubItems.clear();
        listDataSubItems.clear();
        listaSubItems = appCaptureUrl->getLisSubItems();
        subItemsMode = true;
        contadorSubItems = 0;
        startDownSubItems();
        break;
    }
}
