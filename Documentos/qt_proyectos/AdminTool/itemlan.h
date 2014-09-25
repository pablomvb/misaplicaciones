#ifndef ITEMLAN_H
#define ITEMLAN_H

#include <QObject>
#include <QTcpSocket>

class ItemLan : public QObject
{
    Q_OBJECT
    QTcpSocket* socketControl;
    QString ip;
    int puerto;
    QString oS;
    QString nameMachine;
    int tEspera;
    int index;
    QString info;

public:
    explicit ItemLan(QObject *parent = 0);
    void getIpPuerto(QString ip, int puerto); //1
    void setNameMachine(QString name){nameMachine = name;}
    bool isConectado();
    void initConeccion();
    void setIndex(int i){index = i;}
    int getIndex(){return index;}
    void setSocketControl(QTcpSocket* socket);
    void updateInfo();

public slots:
    void shell();

signals:
    void infoConeccion(QString info);

};

#endif // ITEMLAN_H
