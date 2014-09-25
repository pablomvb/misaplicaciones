#include "xtractorurlv2.h"
#include "ui_xtractorurlv2.h"
#include "dialogvarconfig.h"
#include <QFile>
#include <QDebug>
#include <QUrl>
#include <QMessageBox>
#include <QPixmap>
#include <QTreeWidgetItem>

XtractorUrlV2::XtractorUrlV2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XtractorUrlV2)
{
    setWindowTitle("XtractorUrl 2");
    ui->setupUi(this);
    debug("");

    connect(ui->btnConfig,SIGNAL(clicked()),this,SLOT(editarscripts()));
    connect(ui->btnAnalizar,SIGNAL(clicked()),this,SLOT(iniciarAnalisis()));
    connect(ui->btnCancelar,SIGNAL(clicked()),this,SLOT(cancelar()));
    connect(ui->btnSelectSpecific,SIGNAL(clicked()),this,SLOT(selec_e()));
    connect(ui->btnAllMark,SIGNAL(clicked()),this,SLOT(selec_all()));
    connect(ui->btnAllUnMark,SIGNAL(clicked()),this,SLOT(selec_noall()));
    connect(ui->btnCopiar,SIGNAL(clicked()),this,SLOT(copytoclipboard()));
    connect(ui->btnRAuto,SIGNAL(clicked()),this,SLOT(redireccion_auto()));
    connect(ui->btnRManual,SIGNAL(clicked()),this,SLOT(redireccion_manual()));
    connect(ui->btnEditar,SIGNAL(clicked()),this,SLOT(editar()));
    
    bColor.setRgb(87,200,0,100);
    isAbortar = false;
    system = QApplication::clipboard();
    loadHead();
    cargarScripts();
}

XtractorUrlV2::~XtractorUrlV2()
{
    delete ui;
}

void XtractorUrlV2::loadHead()
{
    ui->visorUrls->clear();
    QStringList nameLabels;
    nameLabels<<"Url's";
    ui->visorUrls->setColumnCount(1);
    ui->visorUrls->setHeaderLabels(nameLabels);
    QHeaderView* header = ui->visorUrls->header();
    header->setVisible(true);
    header->setSectionResizeMode(0,QHeaderView::Stretch);
}

void XtractorUrlV2::cargarScripts()
{
    QFile archivoScripts;
    listScripts.clear();
    archivoScripts.setFileName("scriptsconfig");
    if(archivoScripts.open(QIODevice::ReadOnly)){
        listScripts = QString(archivoScripts.readAll()).split("\n");
        for(int i = 0; i<listScripts.count(); i++){
            if(listScripts.value(i).count()==0){
                listScripts.removeAt(i);
                i--;
            }
        }
    }
    archivoScripts.close();
}

bool XtractorUrlV2::cargarInstruncciones(QString nombrescript)
{
    int contador = 0;
    bool retorno = true;
    instrucciones.clear();
    if(nombrescript.contains(".")){
        while (!listScripts.value(contador).contains(nombrescript) && contador<listScripts.count()) {
            contador++;
        }
        if(contador<listScripts.count()){
            instrucciones = listScripts.value(contador).split(":::");
        } else{
            retorno = false;
        }
    } else{
        retorno = false;
    }
    return retorno;
}

void XtractorUrlV2::debug(QString msj)
{
    ui->txtDebug->setText(msj);
}

QString XtractorUrlV2::xtractor(QStringList arg, QByteArray data)
{
    std::string clave     = arg.value(0).toStdString();
            int clave_i_l = arg.value(0).count();
            int clave_i_c = 0;
    std::string patron = "";
            //int patron_l;
            int patron_c = 0;
    bool isAnhadirHost = arg.value(1).contains("_HOST");
    QString p_ = arg.value(1);
    if(isAnhadirHost){
        p_.remove("_HOST+");
    }
    patron = p_.toStdString();
    //patron_l = p_.count();

    bool isClaveEncontrada = false;
    bool isGuardar = false;

    QString r = "";

    int data_c = 0;
    int data_l = data.count();

    do{
        if(clave[clave_i_c]==data.at(data_c)){
            clave_i_c++;
            if(clave_i_c==clave_i_l){
                isClaveEncontrada = true;
            }
        } else {
            clave_i_c = 0;
        }
        data_c++;
    }while(data_c<data_l && !isClaveEncontrada);

    if(isClaveEncontrada){
        data_c = data_c - (clave_i_l);
        do{
            if(data.at(data_c)==patron[patron_c]){
                patron_c++;
                if(patron[patron_c]=='*'){
                    isGuardar = true;
                    patron_c++;
                }
            }
            data_c++;
        }while(!isGuardar && data_c<data_l);
        if(isGuardar){
            do{
                r.append(data.at(data_c));
                data_c++;
            }while(data.at(data_c)!=patron[patron_c] && data_c<data_l);
        }
    }
    if(isAnhadirHost){
        r.prepend(instrucciones.value(0));
        r.prepend("http://");
    }
    if(r.count()==0){
        r = "Sin datos";
    }
    return r;
}

QStringList XtractorUrlV2::xtractorList(QStringList arg, QByteArray data)
{
    std::string clave_i   = arg.value(0).toStdString();
            int clave_i_l = arg.value(0).count();
            int clave_i_c = 0;
    std::string clave_f   = arg.value(2).toStdString();
            int clave_f_l = arg.value(2).count();
            int clave_f_c = 0;
    std::string patron = arg.value(1).toStdString();
            int patron_l = arg.value(1).count();
            int patron_c = 0;

    bool isClaveEncontrada = false;
    bool isGuardar = false;
    bool isTerminarBucle = false;

    QStringList r;
    r.clear();
    QString buffer = "";
    QString bufferTitulo ="";
    int c_buffer = 1;

    int data_c = 0;
    int data_l = data.count();

    do{
        if(clave_i[clave_i_c]==data.at(data_c)){
            clave_i_c++;
            if(clave_i_c==clave_i_l){
                isClaveEncontrada = true;
            }
        } else {
            clave_i_c = 0;
        }
        data_c++;
    }while(data_c<data_l && !isClaveEncontrada);

    if(isClaveEncontrada){
        data_c = data_c - (clave_i_l);
        patron_c = 0;
        do{
            if(patron[patron_c]=='_'){
                patron_c++;
                if(patron[patron_c]=='H' && patron[patron_c+1]=='H'){
                    c_buffer = 1;
                    buffer.append("http://");
                    buffer.append(instrucciones.value(0));
                } else if(patron[patron_c]=='T' && patron[patron_c+1]=='T'){
                    c_buffer = 2;
                }
                patron_c = patron_c + 2;
            }

            do{
                if(data.at(data_c)==patron[patron_c]){
                    patron_c++;
                    if(patron[patron_c]=='*'){
                        isGuardar = true;
                        patron_c++;
                    }
                }
                if(clave_f[clave_f_c]==data.at(data_c) && !isGuardar){
                    clave_f_c++;
                    if(clave_f_c==clave_f_l){
                        isTerminarBucle = true;
                    }
                } else {
                    clave_f_c = 0;
                }
                data_c++;
            }while(!isGuardar && data_c<data_l && !isTerminarBucle);

            if(isGuardar && !isTerminarBucle){
                do{
                    switch (c_buffer) {
                    case 1:
                        buffer.append(data.at(data_c));
                        break;
                    case 2:
                        bufferTitulo.append(data.at(data_c));
                        break;
                    }
                    data_c++;
                }while(data.at(data_c)!=patron[patron_c]);
                isGuardar = false;
                patron_c++;
            }

            if(patron_c==patron_l){
                if( c_buffer==2){
                    r<<bufferTitulo+" :: "+buffer;
                    buffer.clear();
                    bufferTitulo.clear();
                } else {
                    r<<buffer;
                    buffer.clear();
                }
                patron_c=0;
            }
            //data_c++;
        }while(!isTerminarBucle && data_c<data_l);
    }
    if(arg.contains("_INVERTIR")){
        QStringList r_;
        for(int i=r.count()-1; i>=0; i--){
            r_<<r.value(i);
        }
        r = r_;
    }
    if(r.count()==0){
        r<<"Sin datos";
    }
    return r;
}

void XtractorUrlV2::limpiar()
{
    loadHead();
    ui->visorUrls->clear();
    ui->vPortada->clear();
    _SubItems.clear();
    _SubItems_list.clear();
    _SubItemUrls.clear();
    ui->txt1Nombre->setText("");
    ui->txt3Estado->setText("");
    ui->txt4NumSubItems->setText("");
    ui->txtArgumento->setPlainText("");
    debug("");
}

void XtractorUrlV2::controlbotones(bool s, int e)
{
    if(e==1){
        ui->btnCancelar->setVisible(!s);
        ui->btnAnalizar->setEnabled(s);
        ui->btnConfig->setEnabled(s);
    }

    if(e<=1){
        ui->btnAllMark->setEnabled(s);
        ui->btnAllUnMark->setEnabled(s);
        ui->btnCopiar->setEnabled(s);
        ui->btnSelectSpecific->setEnabled(s);
        ui->btnRAuto->setEnabled(s);
        ui->btnRManual->setEnabled(s);
        ui->btnEditar->setEnabled(s);
    }
}

void XtractorUrlV2::editarscripts()
{
    DialogVarConfig editor;
    if(editor.exec()==QDialog::Accepted){
        cargarScripts();
    }
}

void XtractorUrlV2::iniciarAnalisis()
{
    isAbortar = false;
    limpiar();
    if(ui->txt2Url->text().count()!=0){
        if(!cargarInstruncciones(QUrl(ui->txt2Url->text()).host())){
            QMessageBox msj;
            msj.setWindowTitle("Error!!!");
            msj.setInformativeText("No se encontro un script para la url");
            msj.exec();
        } else {
            ui->visorUrls->clear();
            limpiar();
            controlbotones(false,1);
            e_basic();
        }
    } else {
        QMessageBox msj;
        msj.setWindowTitle("Error!!!");
        msj.setInformativeText("ingrese una url");
        msj.exec();
    }
}

void XtractorUrlV2::cancelar()
{
    isAbortar = true;
    controlbotones(true,1);
}

void XtractorUrlV2::selec_e()
{
    DialogSelection s;
    s.setWindowTitle("Clave de seleccion");
    if(s.exec()==QDialog::Accepted){
        QStringList clave = s.clave();
        int opcion = 0;
        int contadorCaracteres = 0;
        if(clave.value(0).contains("1")){
            opcion = 1;
        } else if(clave.value(0).contains("=")){
            opcion = '=';
        } else if(clave.value(0).contains(">")){
            opcion = '>';
        } else if(clave.value(0).contains("<")){
            opcion = '<';
        }
        contadorCaracteres = clave.value(1).toInt();
        QTreeWidgetItem* subitem;
        for(int i=0; i<_SubItemUrls.count(); i++){
            subitem = _SubItemUrls.value(i);
            switch (opcion) {
            case 1:
                if(subitem->text(0).contains(clave.value(1))){
                    subitem->setCheckState(0,Qt::Checked);
                }
                break;
            case '=':
                if(subitem->text(0).count()==contadorCaracteres){
                    subitem->setCheckState(0,Qt::Checked);
                }
                break;
            case '>':
                if(subitem->text(0).count()>contadorCaracteres){
                    subitem->setCheckState(0,Qt::Checked);
                }
                break;
            case '<':
                if(subitem->text(0).count()<contadorCaracteres){
                    subitem->setCheckState(0,Qt::Checked);
                }
                break;
            }

        }
    }
}

void XtractorUrlV2::selec_all()
{
    QTreeWidgetItem* subitem;
    for(int i=0; i<_SubItemUrls.count(); i++){
        subitem = _SubItemUrls.value(i);
        subitem->setCheckState(0,Qt::Checked);
    }
}

void XtractorUrlV2::selec_noall()
{
    QTreeWidgetItem* subitem;
    for(int i=0; i<_SubItemUrls.count(); i++){
        subitem = _SubItemUrls.value(i);
        subitem->setCheckState(0,Qt::Unchecked);
    }
}

void XtractorUrlV2::editar()
{
    Editor e;
    if(e.exec()==QDialog::Accepted){
        int opcion = e.opcion();
        QString prmA = e.parametroA();
        QString prmB = e.parametroB();
        QString p_edit;
        for(int i=0; i<_SubItems.count() && !isAbortar; i++){
            QTreeWidgetItem* item = _SubItems.value(i);
            for (int var = 0; var < item->childCount(); ++var) {
                QTreeWidgetItem* uit = item->child(var);
                p_edit = uit->text(0);
                if(uit->checkState(0)==Qt::Checked){
                    switch (opcion) {
                    case 1:
                        p_edit.prepend(prmA);
                        break;
                    case 2:
                        p_edit.append(prmA);
                        break;
                    case 3:
                        p_edit.replace(prmA,prmB);
                        break;
                    case 4:
                        p_edit.remove(prmA);
                        break;
                    }
                    uit->setText(0,p_edit);
                }
            }
        }
    }
}

void XtractorUrlV2::copytoclipboard()
{
    QStringList urls;

    for (int var = 0; var < _SubItemUrls.count(); var++) {
        if(_SubItemUrls.value(var)->checkState(0)==Qt::Checked){
            urls<<_SubItemUrls.value(var)->text(0);
        }
    }

    system->setText(urls.join("\n"));
}

void XtractorUrlV2::e_basic()
{
    //DownManager xdm;
    QByteArray d_proces;
    bool isDataDown = false;

    if(xdm.urlDownload(ui->txt2Url->text())==1 && !isAbortar){
        debug("Datos descargados ... Procesando datos");
        isDataDown = true;
        d_proces = xdm.dataDownload();
    } else {
        debug("No puedo descargar los datos");
    }

    if(isDataDown && !isAbortar){
        //Nombre
        ui->txt1Nombre->setText(xtractor(instrucciones.value(2).split(";"),d_proces));
        debug("Listo : Nombre");
    }

    if(isDataDown && !isAbortar){
        //Argumento
        QString argTxt = xtractor(instrucciones.value(3).split(";"),d_proces);
        argTxt = argTxt.replace("&aacute;","á");
        argTxt = argTxt.replace("&eacute;","é");
        argTxt = argTxt.replace("&iacute;","í");
        argTxt = argTxt.replace("&oacute;","ó");
        argTxt = argTxt.replace("&uacute;","ú");
        ui->txtArgumento->setPlainText(argTxt);
        debug("Listo : Argumento");
    }

    if(isDataDown && !isAbortar){
        //Portada
        if(xdm.urlDownload(xtractor(instrucciones.value(4).split(";"),d_proces))==1){
            QPixmap img;
            img.loadFromData(xdm.dataDownload());
            ui->vPortada->setPixmap(img.scaled(ui->vPortada->size(),
                                               Qt::KeepAspectRatio,
                                               Qt::SmoothTransformation));
            debug("Listo : Portada");
        } else{
            debug("No puedo descargar la portada");
        }
    }

    if(isDataDown && !isAbortar){
        //Estado
        ui->txt3Estado->setText(xtractor(instrucciones.value(5).split(";"),d_proces));
        debug("Listo : Estado");
    }

    if(isDataDown && !isAbortar){
        //Subitems
        _SubItems_list = xtractorList(instrucciones.value(6).split(";"),d_proces);
        ui->txt4NumSubItems->setText(QString().setNum(_SubItems_list.count()));
        debug("Listo : Numero SubItems");
    }

    if(isDataDown && !isAbortar){
        QString url;
        bool color = false;
        debug("Procesando Urls SubItems");
        for(int i=0; i<_SubItems_list.count() && !isAbortar; i++){
            debug("Procesando Urls SubItem "+QString().setNum(i+1));
            QTreeWidgetItem* item = new QTreeWidgetItem();

            if(_SubItems_list.value(i).contains(" :: ")){
                url = _SubItems_list.value(i).split(" :: ").value(1);
            } else {
                url = _SubItems_list.value(i);
            }
            if(xdm.urlDownload(url)==1){
                d_proces.clear();
                d_proces = xdm.dataDownload();
            } else {
                d_proces.clear();
            }

            item->setText(0,_SubItems_list.value(i));
            _SubItems<<item;
            if(i%2==0 || i == 0){
                item->setBackgroundColor(0,bColor);
                color = true;
            } else {
                color = false;
            }
            ui->visorUrls->addTopLevelItem(item);
            item->setExpanded(true);

            QStringList list_SubItemUrls = xtractorList(instrucciones.value(7).split(";"),d_proces);
            for(int j=0; j<list_SubItemUrls.count(); j++){
                QTreeWidgetItem* itemurl = new QTreeWidgetItem();
                itemurl->setText(0,list_SubItemUrls.value(j));
                if(!list_SubItemUrls.contains("Sin datos")){
                    itemurl->setCheckState(0,Qt::Unchecked);
                }
                if(color){
                    itemurl->setBackgroundColor(0,bColor);
                }
                _SubItemUrls.append(itemurl);
                item->addChild(itemurl);
                ui->visorUrls->scrollToBottom();
            }
            debug("Listo : Urls SubItem "+QString().setNum(i+1));
        }
        debug("Listo : Urls SubItems");
    }
    isAbortar = false;
    controlbotones(true,1);
    debug("Operaciones completadas");
}

void XtractorUrlV2::redireccion_manual()
{
    Navegador nav;
    int c_checked = 0;
    for(int i=0; i<_SubItems.count() && !isAbortar; i++){
        QTreeWidgetItem* item = _SubItems.value(i);
        for (int var = 0; var < item->childCount() && !isAbortar; ++var) {
            QTreeWidgetItem* uit = item->child(var);
            if(uit->checkState(0)==Qt::Checked){
                c_checked++;
            }
        }
    }

    bool isCheckeds = false;
    if(c_checked>0){
        isCheckeds = true;
    }
    controlbotones(false,1);
    for(int i=0; i<_SubItems.count() && !isAbortar; i++){
        QTreeWidgetItem* item = _SubItems.value(i);
        debug("Redireccionando Urls SubItem "+QString().setNum(i+1));
        qDebug()<<"Redireccionando Urls SubItem "+QString().setNum(i+1);
        for (int var = 0; var < item->childCount(); ++var) {
            QTreeWidgetItem* uit = item->child(var);
            nav.cargarUrl(uit->text(0));
            bool validar = false;
            if(isCheckeds){
                if(uit->checkState(0)==Qt::Checked){
                    validar = true;
                }
            } else {
                validar = true;
            }
            if(validar && uit->text(0).contains(instrucciones.value(0)) && nav.exec()==QDialog::Accepted){
                uit->setText(0,nav.url());
                debug("Listo : Url "+QString().setNum(var+1));
                qDebug()<<"Listo : Url "+QString().setNum(var+1);
                if(nav.isCancelarTodo()==1){
                    i = _SubItems.count();
                    var = item->childCount();
                }
            } else {
                if(nav.isCancelarTodo()==1){
                    i = _SubItems.count();
                    var = item->childCount();
                }
            }
        }
        debug("Listo : Redireccionando Urls SubItem "+QString().setNum(i+1));
        qDebug()<<"Listo : Redireccionando Urls SubItem "+QString().setNum(i+1);
    }
    controlbotones(true,1);
}

void XtractorUrlV2::redireccion_auto()
{
    controlbotones(false,1);
    //DownManager xdm;
    int c_checked = 0;
    for(int i=0; i<_SubItems.count() && !isAbortar; i++){
        QTreeWidgetItem* item = _SubItems.value(i);
        for (int var = 0; var < item->childCount() && !isAbortar; ++var) {
            QTreeWidgetItem* uit = item->child(var);
            if(uit->checkState(0)==Qt::Checked){
                c_checked++;
            }
        }
    }

    bool isCheckeds = false;
    if(c_checked>0){
        isCheckeds = true;
    }
    QString u = "";
    qDebug()<<_SubItems.count()<<"\t"<<_SubItemUrls.count();
    for(int i=0; i<_SubItems.count() && !isAbortar; i++){
        QTreeWidgetItem* item = _SubItems.value(i);
        debug("Redireccionando Urls SubItem "+QString().setNum(i+1));
        qDebug()<<"Redireccionando Urls SubItem "+QString().setNum(i+1);
        for (int var = 0; var < item->childCount() && !isAbortar; ++var) {
            QTreeWidgetItem* uit = item->child(var);
            bool validar = false;
            if(isCheckeds){
                if(uit->checkState(0)==Qt::Checked){
                    validar = true;
                }
            } else {
                validar = true;
            }
            if(validar && uit->text(0).contains(instrucciones.value(0)) && xdm.urlDownload(uit->text(0))==1){
                u = xtractor(instrucciones.value(9).split(";"),xdm.dataDownload());
                if(!u.contains("Sin datos")){
                    uit->setText(0,u);
                }
                debug("Listo : Url "+QString().setNum(var+1));
                qDebug()<<"Listo : Url "+QString().setNum(var+1);
            }
        }
        debug("Listo : Redireccionando Urls SubItem "+QString().setNum(i+1));
        qDebug()<<"Listo : Redireccionando Urls SubItem "+QString().setNum(i+1);
    }
    //ui->btnCancelar->setVisible(false);
    //isAbortar = false;
    controlbotones(true,1);
}
