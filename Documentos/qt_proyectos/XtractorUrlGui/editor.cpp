#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}

int Editor::opcion()
{
    int o;
    if(ui->op1->isChecked()){
        o = 1;
    } else if(ui->op2->isChecked()){
        o = 2;
    } else if(ui->op3->isChecked()){
        o = 3;
    } else if(ui->op4->isChecked()){
        o = 4;
    }
    return o;
}

QString Editor::parametroA()
{
    return ui->txt1->text();
}

QString Editor::parametroB()
{
    return ui->txt2->text();
}
