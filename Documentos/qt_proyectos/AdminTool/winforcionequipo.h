#ifndef WINFORCIONEQUIPO_H
#define WINFORCIONEQUIPO_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class wInforcionEquipo;
}

class wInforcionEquipo : public QWidget
{
    Q_OBJECT
    QTcpSocket* socketControl;
        //datos basicos
        QString rIp;
        int rPort;
        QString rOs;
        QString rNameMachine;
    int tEspera;

public:
    explicit wInforcionEquipo(QWidget *parent = 0);
    ~wInforcionEquipo();
    void setBasicData(QString ip,int port,QString oS, QString nameMachine);
    void setSocketPrt(QTcpSocket* prt);
    void updateLabel();

public slots:
    void shell();

private:
    Ui::wInforcionEquipo *ui;
};

#endif // WINFORCIONEQUIPO_H
