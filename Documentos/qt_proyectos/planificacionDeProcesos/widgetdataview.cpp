#include "widgetdataview.h"
#include "ui_widgetdataview.h"
#include <QTableWidgetItem>
#include <QDebug>
#include <QMessageBox>

widgetDataView::widgetDataView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetDataView)
{
    ui->setupUi(this);
    connect(ui->btnLimpiar,SIGNAL(clicked()),this,SLOT(resetTbl()));
    connect(ui->btnCalcular,SIGNAL(clicked()),this,SLOT(runMetodo()));
    connect(this,SIGNAL(autoCalculo()),this,SLOT(autoRunMetodo()));
    ui->lblOut->setVisible(false);
    ui->tblData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->qRoundRobin = 0;
    this->menor1 = 0;
}

widgetDataView::~widgetDataView()
{
    delete ui;
}

void widgetDataView::runMetodo()
{
    switch (this->metodo) {
    case 1:
        this->runMetodoFCFS(ui->tblData->rowCount());
        break;
    case 2:
        this->runMetodoSJF(ui->tblData->rowCount());
        break;
    case 3:
        this->runMetodoBasadoEnPrioridades(ui->tblData->rowCount());
        break;
    case 4:
        this->runMetodoRoundRobin(ui->tblData->rowCount());
        break;
    case 5:
        this->runMetodoMulticolas(ui->tblData->rowCount());
        break;
    default:
        break;
    }
}

void widgetDataView::autoRunMetodo()
{
    switch (this->metodo) {
    case 1:
        this->runMetodoFCFS(-1);
        break;
    case 2:
        this->runMetodoSJF(ui->tblData->rowCount());
        break;
    case 3:
        this->runMetodoBasadoEnPrioridades(ui->tblData->rowCount());
        break;
    case 4:
        this->runMetodoRoundRobin(ui->tblData->rowCount());
        break;
    case 5:
        this->runMetodoMulticolas(ui->tblData->rowCount());
        break;
    default:
        break;
    }
}

void widgetDataView::setQtime(int i)
{
    this->qRoundRobin = i;
    qDebug()<<this->qRoundRobin;
}

void widgetDataView::runMetodoFCFS(int nDatos)
{
    qDebug()<<"fcfs en marcha";
    int tiempoE = 0;
    int tiempoF = 0;
    for(int contador=0; contador<nDatos; contador++){
        qDebug()<<"\t modo bucle";
        if(contador>0){
            tiempoE = tiempoE + (ui->tblData->item(contador-1,2)->text().toInt());
        }
        tiempoF = tiempoF + (ui->tblData->item(contador,2)->text().toInt());

        QTableWidgetItem* tEspera = new QTableWidgetItem();
        tEspera->setText(QString().setNum(tiempoE));
        QTableWidgetItem* tFinal = new QTableWidgetItem();
        tFinal->setText(QString().setNum(tiempoF));
        QTableWidgetItem* tRetorno = new QTableWidgetItem();
        tRetorno->setText(QString().setNum(tiempoF-(ui->tblData->item(contador,1)->text().toInt())));

        ui->tblData->setItem(contador,3,tEspera);
        ui->tblData->setItem(contador,4,tFinal);
        ui->tblData->setItem(contador,5,tRetorno);

    }

    if(nDatos == -1){
        qDebug()<<"\t modo nuevo item";
        int contador = ui->tblData->rowCount() - 1;
        if(contador > 0){
            tiempoE = (ui->tblData->item(contador-1,3)->text().toInt()) + (ui->tblData->item(contador-1,2)->text().toInt());
            tiempoF = ui->tblData->item(contador-1,4)->text().toInt();
        }
        tiempoF = (tiempoF) + (ui->tblData->item(contador,2)->text().toInt());
        QTableWidgetItem* tEspera = new QTableWidgetItem();
        tEspera->setText(QString().setNum(tiempoE));
        QTableWidgetItem* tFinal = new QTableWidgetItem();
        tFinal->setText(QString().setNum(tiempoF));
        QTableWidgetItem* tRetorno = new QTableWidgetItem();
        tRetorno->setText(QString().setNum(tiempoF-(ui->tblData->item(contador,1)->text().toInt())));

        ui->tblData->setItem(contador,3,tEspera);
        ui->tblData->setItem(contador,4,tFinal);
        ui->tblData->setItem(contador,5,tRetorno);
    }

    nDatos = ui->tblData->rowCount();
    float tiempoP = 0;

    for(int i = 0; i<nDatos; i++){
        tiempoP = tiempoP + (ui->tblData->item(i,3)->text().toFloat());
    }
    tiempoP = tiempoP / (nDatos);
    ui->lblOut->setText("Metodo FCFS no Expulsivo\nTiempo promedio: "+QString().setNum(tiempoP));
    ui->lblOut->setVisible(true);
}

void widgetDataView::runMetodoSJF(int nDatos)
{
    int tiempoEa = 0;
    float tiempoP = 0;
    int vectorTe[nDatos][3];
    for(int i = 0; i<nDatos; i++){
        vectorTe[i][0]=0;
        vectorTe[i][1]=ui->tblData->item(i,1)->text().toInt();
        vectorTe[i][2]=ui->tblData->item(i,2)->text().toInt();
    }
    for(int i = 0; i<nDatos; i++){
        QTableWidgetItem *tEspera = new QTableWidgetItem();
        tiempoEa = 0;
        for(int f = 0; f<nDatos; f++){
                if(vectorTe[f][2]<vectorTe[i][2]){
                    tiempoEa = tiempoEa + vectorTe[f][2];
                }
                else{
                    if(vectorTe[f][2]==vectorTe[i][2] && vectorTe[f][1]<vectorTe[i][1]){
                        tiempoEa = tiempoEa + vectorTe[f][2];
                    }
                }
        }
        tEspera->setText(QString().setNum(tiempoEa));
        ui->tblData->setItem(i,3,tEspera);
        tiempoP = tiempoEa + tiempoP;
    }
    tiempoP = tiempoP / nDatos;
    ui->lblOut->setText("Metodo SJF No Expulsivo\nTiempo promedio: "+QString().setNum(tiempoP));
    ui->lblOut->setVisible(true);
}

void widgetDataView::runMetodoBasadoEnPrioridades(int nDatos)
{
    QStringList listaPrioridades;
    listaPrioridades<<"Tiempo Real"<<"Muy Alta"<<"Alta"<<"Normal"<<"Baja"<<"Muy Baja";
    int vector[nDatos][3];

    for(int contador=0; contador<nDatos; contador++){
        vector[contador][0] = ui->tblData->item(contador,1)->text().toInt();
        vector[contador][1] = ui->tblData->item(contador,2)->text().toInt();
        int cLista = 0;
        while((listaPrioridades.value(cLista).contains(ui->tblData->item(contador,3)->text()))==false){
            cLista++;
        }
        vector[contador][2] = cLista;
    }

    float tiempoP = 0;

    for(int i=0; i<nDatos; i++){
        QTableWidgetItem *tEspera = new QTableWidgetItem();
        int tiempoE = 0;
        for(int f=0;f<nDatos;f++){
            if(vector[f][2]<vector[i][2]){
                tiempoE = tiempoE + vector[f][1];
            }
            else{
                if(vector[f][2]==vector[i][2] && vector[f][1]<vector[i][1]){
                    tiempoE = tiempoE + vector[f][1];
                }
            }
        }
        tEspera->setText(QString().setNum(tiempoE));
        ui->tblData->setItem(i,4,tEspera);
        //tiempoP = tiempoE + tiempoP;
    }
    tiempoP = tiempoP / nDatos;
    ui->lblOut->setText("Metodo Basado en Prioridades No Expulsivo\nTiempo promedio: "+QString().setNum(tiempoP));
    ui->lblOut->setVisible(true);
}

void widgetDataView::runMetodoRoundRobin(int nDatos)
{
    int vector[nDatos][2];
    for(int i=0; i<nDatos; i++){
        vector[i][0]= ui->tblData->item(i,2)->text().toInt();
        vector[i][1]= 0;
    }

    int mayor = 0;
    for(int i=0; i<nDatos; i++){
        if(mayor < vector[i][0]){
            mayor = vector[i][0];
        }
    }

    int nuevasColumnas;
    nuevasColumnas = (mayor / this->qRoundRobin);
    if((mayor % this->qRoundRobin) > 0  ){
        nuevasColumnas++;
    }

    QStringList lista;
    lista<<"Id proceso"<<"Llegada"<<"Duracion"<<"T. Retorno";
    ui->tblData->setColumnCount(lista.count()+nuevasColumnas);
    for(int i=0; i<nuevasColumnas; i++){
        ui->tblData->setColumnWidth(4+i,ui->tblData->rowHeight(0));
        lista<<QString("C").append(QString().setNum(i+1));
    }

    ui->tblData->setHorizontalHeaderLabels(lista);

    QColor cColor;
        cColor.setNamedColor("green");

    int matriz[nDatos][nuevasColumnas];
    int suma = 0;

    QStringList l;

    for(int i=0; i<mayor; i++){
        for(int j=0; j<nDatos; j++){
            matriz[j][i]=0;
            if(vector[j][0]>0){
                if(vector[j][0] < this->qRoundRobin){
                    matriz[j][i] = vector[j][0];
                    vector[j][0] = 0;
                }
                else{
                    matriz[j][i] = matriz[j][i] + this->qRoundRobin;
                    vector[j][0] = vector[j][0] - this->qRoundRobin;
                }
            }
            suma = suma + matriz[j][i];
            if(matriz[j][i]>0){
                vector[j][1] = suma;
                if(i<1){
                    l<<QString().setNum(suma);
                }
                else{
                    l.replace(j,QString().setNum(suma));
                }
                //qDebug()<<matriz[j][i]<<"    "<<vector[j][1]<<"    "<<suma<<"     "<<j;
                QTableWidgetItem* tCiclo = new QTableWidgetItem();
                tCiclo->setText(QString().setNum(matriz[j][i]));
                tCiclo->setBackgroundColor(cColor);
                ui->tblData->setItem(j,i+4,tCiclo);
            }
        }
        //qDebug()<<endl;
    }

    float tPromedio = 0;

    for(int i=0; i<nDatos; i++){
        //qDebug()<<"\t"<<vector[i][1]<<"\t"<<l.value(i);
        QTableWidgetItem* tRespuesta = new QTableWidgetItem();
        tRespuesta->setText(l.value(i));
        ui->tblData->setItem(i,3,tRespuesta);
        tPromedio = tPromedio + (l.value(i).toFloat());
    }

    tPromedio = tPromedio / (l.count());
    ui->lblOut->setText("Metodo Round Robin Expulsivo, C[i] = Iteracion i\nTiempo promedio: "+QString().setNum(tPromedio));
    ui->lblOut->setVisible(true);

    //qDebug()<<endl;
}

void widgetDataView::runMetodoMulticolas(int nDatos)
{
    QStringList cClass;
    for(int i=0; i<nDatos; i++){
        cClass << ui->tblData->item(i,3)->text();
    }

    int p1, p2;
    p1 = cClass.count("Primer plano");
    p2 = cClass.count("Segundo plano");

    int vector[nDatos][6];

    for(int i=0; i<nDatos; i++){
        vector[i][0] = 0;
        vector[i][1] = 0;
        vector[i][2] = 0;
        vector[i][3] = 0;
        vector[i][4] = 0;
        vector[i][5] = 0;
        if(ui->tblData->item(i,3)->text()=="Primer plano"){
            vector[i][0] = ui->tblData->item(i,1)->text().toInt();
            vector[i][1] = ui->tblData->item(i,2)->text().toInt();
        }
        else{
            vector[i][3] = ui->tblData->item(i,1)->text().toInt();
            vector[i][4] = ui->tblData->item(i,2)->text().toInt();
        }
    }


}

void widgetDataView::setMetodo(int metodo)
{
    this->metodo = metodo;
    qDebug()<<"wdv: "<<this->metodo;
    QStringList listaHeader;
    listaHeader<<"Id proceso"<<"Llegada"<<"Duracion";

    if(this->metodo==1){
            listaHeader<<"T. Espera"<<"T. Final"<<"T. Retorno";
    }

    if(this->metodo==2 || this->metodo==4){
            listaHeader<<"T. Retorno";
    }

    if(this->metodo==3){
               listaHeader<<"Prioridad"<<"T. Espera";
    }

    if(this->metodo==5){
            listaHeader<<"Clasificación"<<"T. Retorno";
    }

    ui->lblOut->setText("");
    ui->lblOut->setVisible(false);
    ui->tblData->clearContents();
    ui->tblData->setRowCount(0);
    ui->tblData->setColumnCount(listaHeader.count());
    ui->tblData->setHorizontalHeaderLabels(listaHeader);
}

void widgetDataView::getData(QStringList lista)
{
    bool exec = true;
    qDebug()<<lista;
    if((this->metodo==4 || this->metodo==5) && lista.value(3).toInt()==0){
        QMessageBox* msj = new QMessageBox();
        msj->setText("Ingrese un Q (unidades de tiempo) mayores de Cero");
        msj->show();
        exec = false;
    }
    if(exec == true){
    ui->tblData->setRowCount(ui->tblData->rowCount()+1);

    QTableWidgetItem* it1 = new QTableWidgetItem();
    it1->setText(lista.value(0));
    ui->tblData->setItem((ui->tblData->rowCount())-1,0,it1);
    QTableWidgetItem* it2 = new QTableWidgetItem();
    it2->setText(lista.value(1));
    ui->tblData->setItem((ui->tblData->rowCount())-1,1,it2);
    QTableWidgetItem* it3 = new QTableWidgetItem();
    it3->setText(lista.value(2));
    ui->tblData->setItem((ui->tblData->rowCount())-1,2,it3);

    if(this->metodo == 3  || this->metodo == 5){
        QTableWidgetItem* it4 = new QTableWidgetItem();
        it4->setText(lista.value(3));
        ui->tblData->setItem((ui->tblData->rowCount())-1,3,it4);
    }

    if(this->metodo == 4){
        this->qRoundRobin = lista.value(3).toInt();
    }

    emit this->autoCalculo();
    }
}

void widgetDataView::resetTbl()
{
    ui->tblData->clearContents();
    ui->tblData->setRowCount(0);
    ui->lblOut->setText("");
    ui->lblOut->setVisible(false);
    emit this->getResetIdProceso();
}
