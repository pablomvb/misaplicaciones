#include "windowchat.h"
#include "ui_windowchat.h"
#include <QMessageBox>

windowChat::windowChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::windowChat)
{
    ui->setupUi(this);
    socketChat = new QTcpSocket(this);
}

windowChat::~windowChat()
{
    delete ui;
}

int windowChat::setConectar(QString ip, int puerto)
{
    socketChat->connectToHost(ip,puerto);
    if(!socketChat->waitForConnected(tEspera)){
        QMessageBox msj;
        msj.setInformativeText("No se pudo establecer una linea con el administrador");
        msj.show();
        chatConectado = 0;
        return 0;
    }
    connect(socketChat,SIGNAL(readyRead()),this,SLOT(leerMensaje()));
    chatConectado = 1;
    return 1;
}

void windowChat::leerMensaje()
{
    QString mensaje = socketChat->readAll();
    ui->listWidget->addItem(mensaje);
}

void windowChat::enviarMensaje()
{
    if(chatConectado==1){
        socketChat->write(ui->lineEdit->text().toLatin1());
        socketChat->waitForBytesWritten(0);
    }
    else{
        QMessageBox msj;
        msj.setInformativeText("No se pudo establecer una linea con el administrador");
        msj.show();
    }
}
