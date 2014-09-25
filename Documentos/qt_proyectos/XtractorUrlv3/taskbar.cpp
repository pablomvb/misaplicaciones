#include "taskbar.h"
#include "ui_taskbar.h"
#include "temas.h"

TaskBar::TaskBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskBar)
{
    ui->setupUi(this);
    ui->btnInicio->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnCaptura->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnDescargas->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnEmpaquetar->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnRenombrar->setStyleSheet(Temas().boton_hover_TaskBar());

    connect(ui->btnInicio,SIGNAL(clicked()),this,SLOT(btnInicio_press()));
    connect(ui->btnCaptura,SIGNAL(clicked()),this,SLOT(btnCaptura_press()));
    connect(ui->btnDescargas,SIGNAL(clicked()),this,SLOT(btnDescargas_press()));
    connect(ui->btnEmpaquetar,SIGNAL(clicked()),this,SLOT(btnEmpaquetado_press()));
    connect(ui->btnRenombrar,SIGNAL(clicked()),this,SLOT(btnRenombrar_press()));
    connect(this,SIGNAL(aplicacion(QString)),this,SLOT(cambiarEstado(QString)));

    estado("Inicio");
}

TaskBar::~TaskBar()
{
    delete ui;
}

void TaskBar::estado(QString app)
{
    //if(estado_task_bar!=app){
        estado_task_bar = app;
        emit aplicacion(app);
    //}
}

void TaskBar::btnInicio_press()
{
    estado("Inicio");
}

void TaskBar::btnCaptura_press()
{
   estado("Captura");
}

void TaskBar::btnDescargas_press()
{
    estado("Descargas");
}

void TaskBar::btnEmpaquetado_press()
{
    estado("Empaquetar");
}

void TaskBar::btnRenombrar_press()
{
    estado("Renombrar");
}

void TaskBar::cambiarEstado(QString app)
{
    ui->btnInicio->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnCaptura->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnDescargas->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnEmpaquetar->setStyleSheet(Temas().boton_hover_TaskBar());
    ui->btnRenombrar->setStyleSheet(Temas().boton_hover_TaskBar());

    if(app=="Inicio"){
        ui->btnInicio->setStyleSheet(Temas().boton_press_TaskBar());
    } else if(app=="Captura"){
        ui->btnCaptura->setStyleSheet(Temas().boton_press_TaskBar());
    } else if(app=="Descargas"){
        ui->btnDescargas->setStyleSheet(Temas().boton_press_TaskBar());
    } else if(app=="Empaquetar"){
        ui->btnEmpaquetar->setStyleSheet(Temas().boton_press_TaskBar());
    } else if(app=="Renombrar"){
        ui->btnRenombrar->setStyleSheet(Temas().boton_press_TaskBar());
    }
}
