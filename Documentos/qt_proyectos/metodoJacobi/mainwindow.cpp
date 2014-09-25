#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(sizeTableMatriz(int)));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(initJacobi()));
    ui->spinBox->setMinimum(2);
    ui->spinBox_2->setMinimum(1);
    ui->tblResultado->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTblR()
{
    int sizePx=45;
    int sizeRPx=18;
    int iteraciones = ui->spinBox_2->value()+1;
    int columnas = ui->spinBox->value();
    columnas = (columnas*2)+1;
    ui->tblResultado->setColumnCount(columnas);
    ui->tblResultado->setRowCount(iteraciones);
    for(int i=0;i<iteraciones;i++){
        ui->tblResultado->setRowHeight(i,sizeRPx);
    }
    nameHeaderTblR.clear();
    for(int i=0;i<columnas-1;i++){
        ui->tblResultado->setColumnWidth(i,sizePx);
        QString labelColumn;
        if(i<ui->spinBox->value()){
            labelColumn.setNum(i+1);
            labelColumn.prepend("x[");
            labelColumn.append("][i]");
        }
        else{
            labelColumn.setNum((i+1)-ui->spinBox->value());
            labelColumn.prepend("x[");
            labelColumn.append("][i+1]");
            ui->tblResultado->setColumnWidth(i,sizePx+15);
        }
        nameHeaderTblR<<labelColumn;
    }
    ui->tblResultado->setColumnWidth(columnas-1,sizePx);
    nameHeaderTblR<<"D[i]";
    ui->tblResultado->setHorizontalHeaderLabels(nameHeaderTblR);
    QStringList num;
    for(int i=0;i<=ui->spinBox_2->value();i++){
        QString n;
        n.setNum(i);
        num<<n;
    }
    ui->tblResultado->setVerticalHeaderLabels(num);
}

void MainWindow::numerar()
{
    for(int i=0;i<ui->spinBox->value();i++){
        QTableWidgetItem *item = new QTableWidgetItem();
        QString n;
        n.setNum(i+1);
        item->setText(n);
        ui->tblResultado->setItem(0,i,item);
    }
}

bool MainWindow::validarMatriz()
{
    int filasC = ui->tbl_matriz->rowCount();
    int columnC = ui->tbl_matriz->columnCount();
    columnC = columnC - 1;
    float vectorEcuacion[columnC-1];
    float referencia;
    float referenciaB;
    for(int i=0;i<columnC;i++){
        vectorEcuacion[i] = 0;
    }
    int contador = 0;
    while(contador<columnC){
        int contadorB = 0;
        for(int i=0;i<filasC;i++){
            if(i==contador){
                referencia = ui->tbl_matriz->item(contador,i)->text().toFloat();
            }
            else{
                vectorEcuacion[contadorB] = ui->tbl_matriz->item(contador,i)->text().toFloat();
                contadorB++;
            }
            //qDebug()<<ui->tbl_matriz->item(contador,i)->text().toFloat();
        }
        if(referencia<0){
            referencia = referencia * (-1);
        }
        referenciaB = 0;
        for(int i=0;i<contadorB;i++){
            if(vectorEcuacion[i]<0){
                vectorEcuacion[i] = vectorEcuacion[i] * (-1);
            }
            referenciaB = vectorEcuacion[i] + referenciaB;
        }
        //qDebug()<<referenciaB;
        if(referencia>referenciaB){
            qDebug()<<"\tOK";
        }
        else{
            qDebug()<<"\tError";
            return false;
        }
        //qDebug()<<referencia;
        //for(int i=0;i<filasC-1;i++){
        //    qDebug()<<vectorEcuacion[i];
        //}
        contador++;
    }
    return true;
}

void MainWindow::calcular(int rowF)
{
    qDebug()<<"init calcular";
    int varF = ui->spinBox->value();
    float num;
    QTableWidgetItem *item[varF];
    qDebug()<<"a1";
    for(int j=0;j<varF;j++){
        num = ui->tblResultado->item(rowF,j)->text().toFloat();
        //QTableWidgetItem *itemC = new QTableWidgetItem(calcularItem(rowF,rowF,num));
        item[j] = new QTableWidgetItem(calcularItem(rowF,rowF,num));
        ui->tblResultado->setItem(rowF,(varF + j),item[j]);
    }
    qDebug()<<"a3";
}

QString MainWindow::calcularItem(int varX, int varY, float mulX)
{
    QString fNum;
    fNum.setNum(mulX);
    return fNum;
}

void MainWindow::sizeTableMatriz(int size)
{
    int sizePx=45;
    int sizeRPx=18;
    ui->tbl_matriz->setColumnCount(size+1);
    ui->tbl_matriz->setRowCount(size);
    nameHeaderTbl.clear();
    for(int i=0;i<size;i++){
        ui->tbl_matriz->setColumnWidth(i,sizePx);
        QString labelColumn;
        labelColumn.setNum(i+1);
        labelColumn.prepend("x[");
        labelColumn.append("]");
        nameHeaderTbl<<labelColumn;
        ui->tbl_matriz->setRowHeight(i,sizeRPx);
    }
    ui->tbl_matriz->setColumnWidth(size,sizePx);
    nameHeaderTbl<<"R";
    ui->tbl_matriz->setHorizontalHeaderLabels(nameHeaderTbl);
}

void MainWindow::initJacobi()
{
    ui->label_3->setText("Espere...");
    int iteracion = ui->spinBox_2->value();
    iteracion++;
    if(validarMatriz()){
        initTblR();
        numerar();
        for(int i=0;i<iteracion;i++){
            calcular(i);
        }
    }
    ui->label_3->setText("");
}
