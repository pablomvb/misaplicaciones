#include "scaner.h"
#include <QDebug>
#include <QCoreApplication>
#include <QThread>

Scaner::Scaner(QObject *parent) :
    QObject(parent)
{
    contador = 0;
    input = new QTextStream(stdin);
    dataOutCreateScript = "";
    initProcessSubItems = false;
}

void Scaner::setIdScript(QString id)
{
    idScript = id;
}

void Scaner::setDataRAW(QByteArray data)
{
    QString dataRAW;
    dataRAW = data;
    dataAnalisis = dataRAW.split("\n");
}

int Scaner::loadScript()
{
    return 0;
}

void Scaner::createScript()
{
    qDebug()<<"Name Script: "<<idScript;
    fileScript.setFileName(idScript);
    qDebug()<<"PASOS: \n Obtener nombre: ";
    cmdScript();
    nameValue = dataOutCreateScript;
    qDebug()<<"PASOS: \n Obtener estado: ";
    cmdScript();
    stateValue = dataOutCreateScript;
    qDebug()<<"PASOS: \n Obtener lista sub items: ";
    cmdScript(true);
    emit estado(1);
    while(!initProcessSubItems){
        thread()->msleep(100);
    }
    cmdScript(true);
    exit(0);
}

bool Scaner::validar(QString clave, QString patronExtracion, QString modo)
{
    if(initProcessSubItems){
        dataAnalisis.clear();
        dataAnalisis = listDataSubItemValue.value(contadorDataSubItems).split("\n");
        listUrlsSubItemValue.clear();
    }
    while(!dataAnalisis.value(contador).contains(clave)){
        contador++;
    }
    //qDebug()<<"DATA_RAW: "<<dataAnalisis.value(contador);
    QString str = dataAnalisis.value(contador);
    QString dataSave = "";
    bool save = false;
    int contadorPatron = 0;
    listSubItemValue.clear();
    for(int i = 0; i<str.count(); i++){
        //qDebug()<<"\t"<<str.at(i)<<"\t"<<patronExtracion.at(contadorPatron)<<"\t"<<dataSave;
        if(save == true){
            dataSave.append(str.at(i));
            //qDebug()<<"\t\tsaveData";
        }
        if(str.at(i).toLatin1() == patronExtracion.at(contadorPatron).toLatin1()){
            save = false;
            if(contadorPatron+1==patronExtracion.count()){
                if(modo.contains("null")){
                    break;
                }
                if(modo.contains("mono")){
                    dataSave.chop(1);
                    dataSave.prepend(idScript);
                    dataSave.prepend("http://");
                    //qDebug()<<"Url["<<listSubItemValue.count()<<"]: "<<dataSave;
                    if(initProcessSubItems){
                        listUrlsSubItemValue<<dataSave;
                    }
                    else{
                        listSubItemValue<<dataSave;
                    }
                    contadorPatron = 0;
                }
                dataSave.clear();
            }
            contadorPatron++;
            if(patronExtracion.at(contadorPatron).toLatin1() == '*'){
                save = true;
                //qDebug()<<"\t\tsaveDataEnable";
                contadorPatron++;
            }
            else{
                save = false;
            }
            //qDebug()<<"\t\tchangeItemPatronExtraction: "<<patronExtracion.at(contadorPatron);
        }
    }
    //qDebug()<<"endExtratedData";
    if(modo.contains("null")){
        dataSave.chop(1);
        dataOutCreateScript = dataSave;
    }
    contador++;
    if(dataSave.count()==0 && modo.contains("null")){
        return false;
    }

    return true;
}

void Scaner::cmdScript(bool modeListSubItem)
{
    QString item_ClaveDeBusqueda;
    QString item_Patron;
    QString item_Modo = "null";
    bool ciclo = false;
    contadorDataSubItems = listDataSubItemValue.count();
    contadorDataSubItems--;
    contadorInversoSubItems = 1;
    do{
        qDebug()<<"Clave de Busqueda:";
        item_ClaveDeBusqueda = input->readLine();
        qDebug()<<"Patron de Extraccion:";
        item_Patron = input->readLine();
        if(modeListSubItem==true){
            qDebug()<<"Modo lista (mono/multi): ";
            item_Modo = input->readLine();
        }
        if(initProcessSubItems){
            while(contadorDataSubItems>=0){
                ciclo = validar(item_ClaveDeBusqueda,item_Patron,item_Modo);
                if(ciclo==false){
                    qDebug()<<"\t"+nameValue+" "+QString().setNum(contadorInversoSubItems)+"  :: Sin datos";
                }
                else{
                    qDebug()<<"\t"+nameValue+" "+QString().setNum(contadorInversoSubItems);
                    for(int i=0; i<listUrlsSubItemValue.count(); i++){
                        qDebug()<<"\t\t"+listUrlsSubItemValue.value(i);
                    }
                }
                contadorInversoSubItems++;
                contadorDataSubItems--;
            }
        }
        else{
            ciclo = validar(item_ClaveDeBusqueda,item_Patron,item_Modo);
        }
        if(ciclo==false){
            qDebug()<<"No se pudo extraer los datos";
            if(preguntarSiNo()){
                ciclo = true;
                contador = 0;
            }
            else{
                emit estado(-1);
                ciclo = false;
            }
        }
        else{
            if(!modeListSubItem){
                qDebug()<<"DataOut: "<<dataOutCreateScript;
            }
            else{
                if(!initProcessSubItems){
                    qDebug()<<"Url's subpaginas: "<<listSubItemValue;
                }
            }
            if(preguntarSiNo(1)){
                contador = 0;
                ciclo = true;
            }
            else{
                ciclo = false;
            }
        }
    }while(ciclo);
}

bool Scaner::preguntarSiNo(int nQuestion)
{
    QString respuesta = "";
    do{
        switch (nQuestion) {
        case 0:
            qDebug()<<"¿Desea volver a intentarlo? (Si/No)";
            break;
        case 1:
            qDebug()<<"Los datos son correctos. ¿Reintentar? (Si/No)";
            break;
        }
        respuesta = input->readLine().toLower();
    }while(respuesta.contains("si")!=true && respuesta.contains("no")!=true);
    if(respuesta.contains("si")){
        return true;
    }

    return false;
}

QStringList Scaner::getLisSubItems()
{
    return listSubItemValue;
}

void Scaner::setLisDataSubItems(QStringList data)
{
    listDataSubItemValue = data;
}

void Scaner::startProcessSubItems()
{
    initProcessSubItems = true;
}
