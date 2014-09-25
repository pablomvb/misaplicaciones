#include "gui.h"
#include "ui_gui.h"
#include <QDebug>
#include <QHeaderView>
#include <QCheckBox>
#include <QClipboard>
#include <QApplication>

Gui::Gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    setWindowTitle("Visor");
    InputDataObject = new server();
    InputDataObject->run();
    connect(InputDataObject,SIGNAL(data(QString)),this,SLOT(setData(QString)));
    connect(InputDataObject,SIGNAL(clear()),this,SLOT(clean()));
    connect(ui->btnClipBoard,SIGNAL(clicked()),this,SLOT(CopyToClipBoard()));
    ui->txtError->setText("");
    QStringList nameLabels;
    nameLabels<<"SubItem"<<"Url"<<"ClipBoard";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(nameLabels);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(2,100);
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setVisible(true);
    header->setSectionResizeMode(0,QHeaderView::Fixed);
    header->setSectionResizeMode(1,QHeaderView::Stretch);
    header->setSectionResizeMode(2,QHeaderView::Fixed);

}

Gui::~Gui()
{
    delete ui;
}

void Gui::setData(QString d)
{
    QStringList info = d.split("|%*%|");
    qDebug()<<info;
    int widgetVisor = info.value(0).toInt();
    switch (widgetVisor) {
    case -2:
        ui->txtError->setText(info.value(1));
        //error
        break;
    case 1:
        ui->txtNombre->setText(info.value(1));
        //nombre
        break;
    case -1:
        ui->txtUrl->setText(info.value(1));
        //url
        break;
    case 2:
        ui->txtEstado->setText(info.value(1));
        //estado
        break;
    case 3:
        ui->txtNumSubItems->setText(info.value(1));
        //num subitems
        break;
    case 4:{
        QString d = info.value(1);
        if(info.value(2).contains("No se registro")){
            d = info.value(1).split(":").value(0) + ": 0 de 0";
        }
        int modeColor = info.value(1).split(" : ").value(0).toInt();
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QTableWidgetItem* item = new QTableWidgetItem(d);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,item);
        QTableWidgetItem* item2 = new QTableWidgetItem(info.value(2));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,item2);
        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,item3);
//        item->setFlags(Qt::ItemIsEnabled);
//        item2->setFlags(Qt::ItemIsEnabled);
//        item3->setFlags(Qt::ItemIsEnabled);
        if(modeColor%2 == 0 || modeColor == 0){
            QColor color;
            color.setRgb(0,122,0);
            item->setBackgroundColor(color);
            item2->setBackgroundColor(color);
            item3->setBackgroundColor(color);
        }
        //urls subitems
    }
        break;
    case 10:
        QTableWidgetItem* item;
        for (int var = 0; var < ui->tableWidget->rowCount(); var++) {
            item = ui->tableWidget->item(var,0);
            if(item->text().contains(info.value(1))){
                ui->tableWidget->removeRow(var);
                var--;
            }
        }
        //remover urls subItem
        break;
    }
}

void Gui::clean()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QStringList nameLabels;
    nameLabels<<"SubItem"<<"Url"<<"ClipBoard";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(nameLabels);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(2,100);
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setVisible(true);
    header->setSectionResizeMode(0,QHeaderView::Fixed);
    header->setSectionResizeMode(1,QHeaderView::Stretch);
    header->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->txtError->clear();
    ui->txtEstado->clear();
    ui->txtNombre->clear();
    ui->txtNumSubItems->clear();
    ui->txtUrl->clear();
}

void Gui::CopyToClipBoard()
{
    QStringList listaCopyToClipBoard;
    QTableWidgetItem* item;
    QTableWidgetItem* item2;
    for (int var = 0; var < ui->tableWidget->rowCount(); var++) {
        item = ui->tableWidget->item(var,1);
        item2 = ui->tableWidget->item(var,2);
        if(item2->checkState()==Qt::Checked){
            if(!item->text().contains("No se registro")){
                listaCopyToClipBoard<<item->text();
            }
        }
    }
    QClipboard *system = QApplication::clipboard();
    system->setText(listaCopyToClipBoard.join("\n"));
}
