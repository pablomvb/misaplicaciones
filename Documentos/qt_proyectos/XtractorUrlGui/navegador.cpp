#include "navegador.h"
#include "ui_navegador.h"

Navegador::Navegador(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Navegador)
{
    ui->setupUi(this);
    cancelar_todo = 0;
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(c_all()));
    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(setUrl(QUrl)));
    setWindowTitle("RedirTool");
    ui->urlNueva->setText("");
}

Navegador::~Navegador()
{
    delete ui;
}

void Navegador::cargarUrl(QString url)
{
    ui->urlOriginal->setText(url);
    ui->webView->load(QUrl(url));
    ui->urlNueva->setText("");
}

QString Navegador::url()
{
    QString r;
    if(ui->urlNueva->text().count()==0){
        r = ui->urlOriginal->text();
    } else {
        r = ui->urlNueva->text();
    }
    return r;
}

void Navegador::setUrl(QUrl newUrl)
{
    ui->urlNueva->setText(newUrl.toString());
}

void Navegador::c_all()
{
    cancelar_todo = 1;
    close();
}
