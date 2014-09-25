#include "xtractorurl.h"

XtractorUrl::XtractorUrl(QObject *parent) :
    QObject(parent)
{
    visorOut = false;
    write("XtractorUrl\n",0);
    visor = new QTcpSocket(this);
    input = new QTextStream(stdin);
    arg = QCoreApplication::instance()->arguments();
    scriptFile.setFileName("xtractorUrlScript.config");
    modeCreateScript = false;
    if(scriptFile.open(QIODevice::ReadOnly)){
        scriptSelect = scriptFile.readAll();
        scriptFile.close();
        if(scriptSelect.count()!=0){
            scriptList = scriptSelect.split("\n");
        }
    }
    scriptSelect.clear();
    scriptSelectI.clear();
    analisiModoUrlsSubItems = false;
    contadorIteracionData = 0;
    scriptSave = false;
    continuarEjecucion = true;
    modeCreateScript = false;
    modeCreateScript = false;
    informeContadorSaveData = 0;
    informeContadorSaveData2 = 0;
    informeOpen = false;
    numUrlsSubItems = 0;
    connect(this,SIGNAL(mensajero(int)),this,SLOT(estado(int)));
    connect(this,SIGNAL(setUrl(QString)),this,SLOT(downDataUrl(QString)));
    connect(this,SIGNAL(initAnalisis()),this,SLOT(analisis()));
    connect(this,SIGNAL(initAnalisisSubItems()),this,SLOT(analisisSubItems()));
    connect(this,SIGNAL(downSubItem()),this,SLOT(downSubItems()));
    connect(visor,SIGNAL(disconnected()),this,SLOT(disableVisor()));
}

void XtractorUrl::start()
{
    visor->connectToHost("localhost",6509);
    if(visor->waitForConnected(200)){
        visorOut = true;
    }

    QUrl urlAnalizar;

    if(arg.count()>1){
            urlAnalizar = arg.value(1);
            if(urlAnalizar.isValid()){
                write("Url: "+urlAnalizar.toString()+"\n",0);
            }
            else{
                errorBuffer = "Url no valida";
                continuarEjecucion = false;
                mensajero(-1);
            }

    }
    else{
        continuarEjecucion = true;
        write("Url: ",0);
        urlAnalizar = read();
        if(urlAnalizar.isValid()){
            continuarEjecucion = true;
        }
        else{
            errorBuffer = "Url no valida";
            continuarEjecucion = false;
            mensajero(-1);
        }
    }

    if(continuarEjecucion){
        QString nameScript = urlAnalizar.host();
        if(!analisisScript(nameScript)){
            scriptSelectI<<nameScript;
        }
        if(continuarEjecucion){
            write("Nombre del Script: "+nameScript+"\n\n",0);
            emit setUrl(urlAnalizar.toString());
        }
        else{
            emit mensajero(-1);
        }
    }
}


QString XtractorUrl::read()
{
    return input->readLine();
}

void XtractorUrl::write(QString label, int widgetVisor)
{
    QTextStream out(stdout);
    out<<label;
    out.flush();
    bool emitir = true;
    if(label.contains("::")){
        emitir = false;
    }
    else if(label.contains("Url registradas:")){
        emitir = false;
    }
    if(visorOut && emitir && widgetVisor != 0){
        QString num;
        num.setNum(widgetVisor);
        num.append("|%*%|");
        QStringList list;
        if(widgetVisor==-2){
            label = num+"Error: "+errorBuffer;
        }
        else if(widgetVisor==4){
            numUrlsSubItems_UrlSelect++;
            QString n;
            n.setNum(numUrlsSubItems_UrlSelect);
            QString n2;
            n2.setNum(numUrlsSubItems_UrlSelect);
            label.remove("\t\t\t");
            label = num+QString().setNum(itemContadorSubItemsSelect+1)+" : "+n+" de "+n2+"|%*%|"+label;
        }
        else if(widgetVisor==10){
            label = num+QString().setNum(itemContadorSubItemsSelect+1)+" : ";
        }
        else{
            list = label.split(": ");
            label = num+list.value(1);
        }

//        case -2:
//            //error
//        case 1:
//            //nombre
//        case -1:
//            //url
//        case 2:
//            //estado
//        case 3:
//            //num subitems
//        case 4:
//            //urls subitems
//        case 10:
//            //remover urls subItem

        visor->write(label.toLatin1());
        visor->waitForBytesWritten(0);
    }
}

bool XtractorUrl::analisisScript(QString nameScript)
{
    bool r = false;
    for(int i=0; i<scriptList.count(); i++){
        scriptSelect = scriptList.value(i);
        if(scriptSelect.contains(nameScript)){
            r = true;
            i = scriptList.count();
            scriptSelectI = scriptSelect.split("|");
        }
    }
    if(!r){
        errorBuffer = "No se encontro un script para procesar la url";
        if(siNO("No se encontro ningun script que pueda procesar esta Url, ¿Desea crearlo?")){
            modeCreateScript = true;
            write("Modo CreateScript = enable\n",0);
        }
        else{
            continuarEjecucion = false;
        }
    }
    return r;
}

void XtractorUrl::downDataUrl(QString url)
{
    data.clear();
        write("Descargando: "+url,0);
    this->url = url;
    reply = qnam.get(QNetworkRequest(this->url));
    connect(reply,SIGNAL(finished()),this,SLOT(finDownFile()));
    connect(reply,SIGNAL(readyRead()),this,SLOT(leerDownFile()));
}

bool XtractorUrl::analisis(QString script, int idBuffer)
{
    QStringList scriptCmd = script.split(";");

    int modo = 0;

    if(scriptCmd.count()>2){
        if(scriptCmd.value(2).contains("mono")){
            modo = 1;
        }
        else if(scriptCmd.value(2).contains("multi")){
            modo = 2;
        }
    }

    QString clave = scriptCmd.value(0);
    bool finBucle = false;
    bool errorBucleBusquedaPorClave = false;

    if(modeAnlisisSubItems){
        contadorIteracionData = 0;
    }

    bool sin_datos = false;

    while(!dataAnalisis.value(contadorIteracionData).contains(clave) && finBucle==false){
        contadorIteracionData++;
        if(contadorIteracionData==dataAnalisis.count()){
            finBucle = true;
            if(modeAnlisisSubItems){
                sin_datos = true;
                errorBucleBusquedaPorClave =false;
            }
            else{
                errorBucleBusquedaPorClave = true;
            }
            errorBuffer = "No se entontro la ningun dato para procesar con la clave de busqueda: "+clave;
        }
    }

    std::string patron = scriptCmd.value(1).toStdString();
    int sizePatron = scriptCmd.value(1).count();
    QString d;
    if(!sin_datos){
        d = dataAnalisis.value(contadorIteracionData);
    }
    else{
        d = "";
    }
    if(scriptCmd.count()==4){
        QStringList lClave = scriptCmd.value(3).split("%");
        if(itemState.contains(lClave.value(1))){
            d = d.split(lClave.value(0)).value(0);
        }
    }
    std::string dataRAW = d.toStdString();
    if(modeCreateScript && !errorBucleBusquedaPorClave){
        write("DataSelet: "+d+"\n",0);
    }
    int sizeDataRAW = d.count();
    QString dataSave = "";
    bool save = false;
    int contadorPatron = 0;

    if(idBuffer==3 && !errorBucleBusquedaPorClave){
        itemListSubItems.clear();
    }

    QStringList subItemsUrls;
    if(!errorBucleBusquedaPorClave){
        for (int var = 0; var < sizeDataRAW; var++) {
            if(dataRAW[var]==patron[contadorPatron]){
                contadorPatron++;
            }
            if(patron[contadorPatron]=='*'){
                save = true;
                var++;
                contadorPatron++;
            }
            while (save==true && dataRAW[var]!=patron[contadorPatron]) {
                dataSave.append(dataRAW[var]);
                var++;
            }
            save = false;
            if(sizePatron == contadorPatron+1){
                switch (modo) {
                case 0:
                    var = sizeDataRAW;
                    break;
                case 1:
                    contadorPatron = 0;
                    subItemsUrls<<dataSave;
                    dataSave.clear();
                    break;
                case 2:
                    write("Modo multiLinea en implementacion\n",0);
                    var = sizeDataRAW;
                    break;
                }
            }
        }

        switch (idBuffer) {
        case 1:
            itemName = dataSave;
            saveDataFile<<"Nombre Item: "+itemName;
            saveDataFile<<"Url Item: "+url.toString();
            break;
        case 2:
            itemState = dataSave;
            saveDataFile<<"Estado Item: "+itemState;
            break;
        case 3:
            saveDataFile<<"Numero de subItems: "+QString().setNum(subItemsUrls.count());
            for (int i = 0; i<subItemsUrls.count(); i++) {
                itemListSubItems.prepend("http://"+scriptSelectI.value(0)+subItemsUrls.value(i));
            }
            if(modeCreateScript){
                for(int i=0;i<itemListSubItems.count();i++){
                    write("\t"+itemListSubItems.value(i)+"\n",0);
                }
            }
            break;
        case 4:
            QString d;
            d.setNum(itemContadorSubItemsSelect+1);
            d.prepend("\tSubItem ");
            d.append(" :: "+itemListSubItems.value(itemContadorSubItemsSelect));
            QString numUrls = "\t\tUrl registradas: "+QString().setNum(subItemsUrls.count());
            numUrlsSubItems = subItemsUrls.count();
            numUrlsSubItems_UrlSelect = 0;
            //itemListSubItemsUrls<<d;
            saveDataFile<<d;
            saveDataFile<<numUrls;
            if(modeCreateScript){
                write(d+"\n",0);
                write(numUrls+"\n",0);
            }
            for(int i=0;i<subItemsUrls.count();i++){
                QString direcctionEncode = "\t\t\t"+decodUrl(subItemsUrls.value(i));
                saveDataFile<<direcctionEncode;
                if(modeCreateScript){
                    write(direcctionEncode+"\n",0);
                }
            }
            break;
        }
        errorBuffer = "No se registro datos con el patron de extracion: "+scriptCmd.value(1);
    }
    bool r = true;
    if(errorBucleBusquedaPorClave){
        r = false;
    }
    else if(idBuffer==1 || idBuffer==2){
        if(dataSave.count()==0){
            r = false;
        }
        r = true;
    }
    else if(idBuffer==3){
        if(subItemsUrls.count()==0){
            r = false;
        }
        r = true;
    }
    else if(idBuffer==4){
        if(subItemsUrls.count()==0){
            saveDataFile<<"\t\t\tNo se registro Urls";
        }

        r = true;
    }
    return r;
}

bool XtractorUrl::analisisModoCreateScript(QString label, int idBufer)
{
    bool bucle = true;
    write(label,0);
    if(idBufer==3 || idBufer==4){
        scriptSelectI<<addScriptCmd(true);
    }
    else{
        scriptSelectI<<addScriptCmd();
    }
    bucle = analisis(scriptSelectI.value(idBufer),idBufer);
    if(!bucle){
        write("Error: "+errorBuffer+"\n",0);
        errorBuffer = "Sin exito al intentar completar las operaciones";
        bucle = siNO("No se pudo extraer los datos. ¿Desea volver a intentarlo?");
        if(!bucle){
            emit mensajero(-1);
        }
        bucle = !bucle;
        contadorIteracionData = 0;
    }
    else{
        if(idBufer==4 && saveDataFile.value(saveDataFile.count()-1).contains("No se registro Urls") && modeCreateScript){
            write("Nota: Si no se registro ninguna url, pruebe cambiando los valores del script de extraccion\n",0);
        }

        bucle = siNO("¿Los datos son correctos?");
        if(!bucle){
            bucle = siNO("¿Desea volver a intentarlo?");
            if(!bucle){
                emit mensajero(-1);
            }
            bucle = !bucle;
        }
    }
    return bucle;
}

QString XtractorUrl::addScriptCmd(bool listSubItem)
{
    QStringList buffer;

    write("Clave de busqueda: ",0);
    buffer<<read();
    write("Patron de extracion: ",0);
    buffer<<read();
    if(listSubItem){
        write("Modo de busqueda de Urls (monoLine/multiLinea): ",0);
        buffer<<read();
        if(siNO("¿Desea agregar una clave para saltar subItems vacios?")){
            QStringList lClaveBuffer;
            write("Clave de salto: ",0);
            lClaveBuffer<<read();
            write("Activador de clave: ",0);
            lClaveBuffer<<read();
            buffer<<lClaveBuffer.join("%");
        }
    }

    return buffer.join(";");
}

bool XtractorUrl::siNO(QString label)
{
    label.append(" (Si/No): ");
    int respuesta = 0;
    do{
        write(label,0);
        QString r = read().toLower();
        if(r.contains("si")){
            respuesta = 1;
        }
        else if(r.contains("no")){
            respuesta = -1;
        }
        else{
            respuesta = 0;
        }
    }while (respuesta==0);

    if(respuesta == -1){
        return false;
    }
    return true;
}

void XtractorUrl::analisisError(bool output, int buffer)
{
    if(!output){
        emit mensajero(-1);
    }
    else{
        switch (buffer) {
        case 1:
            write(saveDataFile.value(informeContadorSaveData)+"\n",1);
            informeAddDato(saveDataFile.value(informeContadorSaveData));
            informeContadorSaveData++;
            write(saveDataFile.value(informeContadorSaveData)+"\n",-1);
            informeAddDato(saveDataFile.value(informeContadorSaveData));
            informeContadorSaveData++;
            break;
        case 2:
            write(saveDataFile.value(informeContadorSaveData)+"\n",2);
            informeAddDato(saveDataFile.value(informeContadorSaveData));
            informeContadorSaveData++;
            break;
        case 3:
            write(saveDataFile.value(informeContadorSaveData)+"\n",3);
            informeAddDato(saveDataFile.value(informeContadorSaveData));
            informeContadorSaveData++;
            break;
        case 4:
            do{
                write(saveDataFile.value(informeContadorSaveData)+"\n",4);
                informeAddDato(saveDataFile.value(informeContadorSaveData));
                informeContadorSaveData++;
            }while(informeContadorSaveData<saveDataFile.count());
            break;
        }
    }

}

void XtractorUrl::informeAddDato(QString dato)
{
    dato.append("\n");
    QByteArray buffer;
    buffer.append(dato);
    if (!informeOpen) {
        informe.setFileName(itemName.replace(" ","_")+".outUrls");
        openForWrite_informe();
    }
    informe.write(buffer);
    informe.waitForBytesWritten(0);
}

void XtractorUrl::openForWrite_informe()
{
    if(informe.open(QIODevice::ReadOnly)){
        if(siNO("Ya existe un archivo sobre este item. ¿Desea sobrescribirlo?")){
            informe.close();
            if(informe.remove()){
                if(!informe.open(QIODevice::WriteOnly)){
                    if(siNO("No pudo crear el archivo, ¿Desea usar otro nombre?")){
                        write("Nuevo nombre: ",0);
                        informe.setFileName(read());
                        openForWrite_informe();
                    }
                    else{
                        errorBuffer = "No se pudo crear el archivo del item";
                        mensajero(-1);
                    }
                }
                else{
                    informeOpen = true;
                }
            }
            else{
                errorBuffer = "No se pudo eliminar el archivo mencionado";
                mensajero(-1);
            }
        }
        else{
            write("Los nuevos datos seran añadidos al final del archivo\n",0);
            if(informe.open(QIODevice::ReadWrite)){
                informeOpen = true;
                informeAddDato("\n================================================================================\n");
            }
            else{
                errorBuffer = "El archivo tiene habilitada la proteccion contra escritura";
                mensajero(-1);
            }
        }
    }
    else{
        if(informe.open(QIODevice::WriteOnly)){
            informeOpen = true;
        }
        else{
            errorBuffer = "No se pudo escribir el archivo";
            mensajero(-1);
        }
    }
}

void XtractorUrl::finDownFile()
{
    disconnect(reply,SIGNAL(finished()),this,SLOT(finDownFile()));
    disconnect(reply,SIGNAL(readyRead()),this,SLOT(leerDownFile()));
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(reply->error()){
        data.clear();
        errorBuffer = "No se pudo descargar los datos";
        emit estado(-1);
    } else if(!redirectionTarget.isNull()){
        QUrl newUrlDirection = url.resolved(redirectionTarget.toUrl());
        emit estado(0);
        reply->~QNetworkReply();
        reply = 0;
        emit setUrl(newUrlDirection.toString());
    }
    else{
        reply->~QNetworkReply();
        reply = 0;
        emit estado(1);
    }
}

void XtractorUrl::leerDownFile()
{
    data.append(reply->readAll());
}

void XtractorUrl::disableVisor()
{
    visorOut = false;
}

void XtractorUrl::estado(int estado)
{
    switch (estado) {
    case -1:
    {
        write("\nError: "+errorBuffer+"\n",-2);
        if(informeOpen){
            informeAddDato("\nError: "+errorBuffer);
            informe.close();
        }
        exit(-1);
    }
    break;
    case 0:
    {
        write(" : Redireccion de url",0);
    }
    break;
    case 1:
    {
        if(data.count()>0){
            write(" : OK\n",0);
        }
        else{
            write(" : Error!!!\n",0);
            mensajero(-1);
        }
        dataAnalisis = data.split("\n");
        if(!modeAnlisisSubItems){
            emit initAnalisis();
        }
        else{
            emit initAnalisisSubItems();
        }
    }
    break;
    case 2:
    {
        if(modeCreateScript){
            if(scriptSave){
                scriptFile.open(QIODevice::WriteOnly);
                scriptSelect = scriptSelectI.join("|")+"\n";
                scriptFile.write(scriptSelect.toLatin1());
                scriptFile.waitForBytesWritten(0);
                scriptFile.close();
            }
        }
        if(informeOpen){
            informe.close();
        }
        exit(0);
    }
    break;
    case 3:
    {
        itemContadorSubItemsSelect++;
        if(itemContadorSubItemsSelect==itemListSubItems.count()){
            emit mensajero(2);
        }
        else{
            emit downSubItem();
        }
    }
    break;
    }
}

void XtractorUrl::analisis()
{
//    switch (buffer) {
//    case 1:
//        write(saveDataFile.value(informeContadorSaveData));
//        informeAddDato(saveDataFile.value(informeContadorSaveData));
//        contadorIteracionData++;
//        write(saveDataFile.value(informeContadorSaveData));
//        informeAddDato(saveDataFile.value(informeContadorSaveData));
//        contadorIteracionData++;
//        break;
//    case 2:
//        write(saveDataFile.value(informeContadorSaveData));
//        informeAddDato(saveDataFile.value(informeContadorSaveData));
//        contadorIteracionData++;
//        break;
//    case 3:
//        write(saveDataFile.value(informeContadorSaveData));
//        informeAddDato(saveDataFile.value(informeContadorSaveData));
//        contadorIteracionData++;
//        break;
//    case 4:
//        do{
//            write(saveDataFile.value(informeContadorSaveData));
//            informeAddDato(saveDataFile.value(informeContadorSaveData));
//            contadorIteracionData++;
//        }while(informeContadorSaveData<saveDataFile.count());
//        break;
//    }

    bool bucle = true;
    // name
    if(modeCreateScript){
        do{
            if(bucle==false){
                scriptSelectI.removeLast();
                saveDataFile.removeLast();
                saveDataFile.removeLast();
                informeContadorSaveData--;
                informeContadorSaveData--;
            }
            bucle = analisisModoCreateScript("Obtener Nombre\n",1);
            write(saveDataFile.value(informeContadorSaveData)+"\n",1);
            informeContadorSaveData++;
            write(saveDataFile.value(informeContadorSaveData)+"\n",-1);
            informeContadorSaveData++;
        }while(!bucle);
        informeAddDato(saveDataFile.value(informeContadorSaveData2));
        informeContadorSaveData2++;
        informeAddDato(saveDataFile.value(informeContadorSaveData2));
        informeContadorSaveData2++;
    }
    else{
        analisisError(analisis(scriptSelectI.value(1),1),1);
    }

    // state
    if(modeCreateScript){        
        do{
            if(bucle==false){
                scriptSelectI.removeLast();
                saveDataFile.removeLast();
                informeContadorSaveData--;
            }
            bucle = analisisModoCreateScript("Obtener Estado\n",2);
            write(saveDataFile.value(informeContadorSaveData)+"\n",2);
            informeContadorSaveData++;
        }while(!bucle);
        informeAddDato(saveDataFile.value(informeContadorSaveData2));
        informeContadorSaveData2++;
    }
    else{
        analisisError(analisis(scriptSelectI.value(2),2),2);
    }
    // subItems
    if(modeCreateScript){    
        do{
            if(bucle==false){
                scriptSelectI.removeLast();
                saveDataFile.removeLast();
                informeContadorSaveData--;
            }
            bucle = analisisModoCreateScript("Obtener SubItems\n",3);
            write(saveDataFile.value(informeContadorSaveData)+"\n",3);
            informeContadorSaveData++;
        }while(!bucle);
        informeAddDato(saveDataFile.value(informeContadorSaveData2));
        informeContadorSaveData2++;
    }
    else{
        analisisError(analisis(scriptSelectI.value(3),3),3);
    }

    // url's subItems
    itemContadorSubItemsSelect = 0;
    modeAnlisisSubItems = true;
    emit downSubItem();
}

void XtractorUrl::analisisSubItems()
{
    bool bucle = true;
    if(modeCreateScript && itemContadorSubItemsSelect==0){
        do{
            if(bucle==false){
                scriptSelectI.removeLast();
                while(!saveDataFile.value(saveDataFile.count()-1).contains("Numero de subItems")) {
                    saveDataFile.removeLast();
                    informeContadorSaveData--;
                }
                write("",10);
            }
            bucle = analisisModoCreateScript("Obtener Urls SubItems\n",4);
            do{
                write(saveDataFile.value(informeContadorSaveData)+"\n",4);
                informeContadorSaveData++;
            }while(informeContadorSaveData<saveDataFile.count());
        }while(!bucle);
        do{
            informeAddDato(saveDataFile.value(informeContadorSaveData2));
            informeContadorSaveData2++;
        }while(informeContadorSaveData2<saveDataFile.count());
        scriptSave = true;
    }
    else{
        analisisError(analisis(scriptSelectI.value(4),4),4);
    }
    emit mensajero(3);
}

void XtractorUrl::downSubItems()
{
    QString d;
    d.setNum(itemContadorSubItemsSelect+1);
    write("\n",0);
    if(modeCreateScript){
        write("\nSubItem "+d+"\n",0);
    }
    downDataUrl(itemListSubItems.value(itemContadorSubItemsSelect));
}

QString XtractorUrl::decodUrl(QString urlCod)
{
//    while(urlCod.at(0).toLatin1()!='='){
//        urlCod.remove(0,1);
//    }
//    urlCod.remove(0,1);

//    http://www.e-planning.net/es/soporte/codificacion_caracteres_en_url.html
//    http://www.zainex.es/guia-rapida/html/html-url-encode-codificacion

//    write("\n",0);
//    urlCod = urlCod.replace("%20"," ");
//    urlCod = urlCod.replace("%23","#");
//    urlCod = urlCod.replace("%25","%");
//    urlCod = urlCod.replace("%26","&");
    urlCod = urlCod.replace("%2f","/");
    urlCod = urlCod.replace("%2F","/");
    urlCod = urlCod.replace("%3a",":");
    urlCod = urlCod.replace("%3A",":");
//    urlCod = urlCod.replace("%3b",";");
//    urlCod = urlCod.replace("%3B",";");
//    urlCod = urlCod.replace("%3c","<");
//    urlCod = urlCod.replace("%3C","<");
//    urlCod = urlCod.replace("%3d",">");
//    urlCod = urlCod.replace("%3D",">");
//    urlCod = urlCod.replace("%3f","?");
//    urlCod = urlCod.replace("%3F","?");
//    urlCod = urlCod.replace("%7c","|");
//    urlCod = urlCod.replace("%7C","|");
    return urlCod;
}
