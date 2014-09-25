#include "pkgcbfile.h"
#include "ui_pkgcbfile.h"

pkgCBFile::pkgCBFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pkgCBFile)
{
    ui->setupUi(this);
    connect(ui->btnSelectFolder,SIGNAL(clicked()),this,SLOT(selectFolder()));
}

pkgCBFile::~pkgCBFile()
{
    delete ui;
}

void pkgCBFile::selectFolder()
{
    ui->listWidget->clear();
    selectFIles.setFileMode(QFileDialog::Directory);
    if(selectFIles.exec()==QFileDialog::Accepted){
        ui->listWidget->addItems(QDir(selectFIles.directory()).entryList());
        ui->lineEdit->setText(selectFIles.directoryUrl().toString());
    }
}
