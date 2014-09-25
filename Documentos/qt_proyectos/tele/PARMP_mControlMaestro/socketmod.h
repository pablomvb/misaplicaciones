#ifndef SOCKETMOD_H
#define SOCKETMOD_H

#include <QTcpSocket>
#include <QHostAddress>

class socketMod : public QTcpSocket
{
    Q_OBJECT
    int indexItem;
    QHostAddress ipRemota;
    QString nombreEquipo;
    int portRemoto;
    int portDisplay;
    int portKeyboard;
    int portMouse;
    int comando;

public:
    explicit socketMod(QString ip, int port, QObject *parent = 0);
    void setIpRemota(QString ip);
    void setPortRemoto(int port){portRemoto = port;}
    void setPortDisplay(int display){portDisplay = display;}
    void setPortKeyboard(int keyboard){ portKeyboard = keyboard;}
    void setPortMouse(int mouse){ portMouse = mouse;}
    void iniciar();
    QString getIp(){return ipRemota.toString();}
    QString getNombreEquipot(){return nombreEquipo;}

signals:

public slots:
    void shell();

};

#endif // SOCKETMOD_H
