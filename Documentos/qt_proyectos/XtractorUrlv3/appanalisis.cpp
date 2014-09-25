#include "appanalisis.h"
#include "ui_appanalisis.h"

AppAnalisis::AppAnalisis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppAnalisis)
{
    ui->setupUi(this);
}

AppAnalisis::~AppAnalisis()
{
    delete ui;
}
