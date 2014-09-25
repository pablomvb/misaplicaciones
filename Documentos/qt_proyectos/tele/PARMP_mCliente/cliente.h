#ifndef CLIENTE_H
#define CLIENTE_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QPixmap>
#include "camara.h"

namespace Ui {
class Cliente;
}

class Cliente : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cliente(QWidget *parent = 0);
    ~Cliente();
    void setupCliente();

public slots:
    void shell();
    void coneccionEntrante();
    void clienteDesconectado();

private:
    Ui::Cliente *ui;
    Camara* camaraWeb;

    QString ipLocal;
    int portLocal;
    QString userName;
    bool controActivo;
    int comando;

    QTcpServer* servidorControl;
    QTcpSocket* socketControl;
    //QTcpSocket* socketDisplay;
    QTcpSocket* socketKeyboar;
    QTcpSocket* socketMouse;

};

#endif // CLIENTE_H
