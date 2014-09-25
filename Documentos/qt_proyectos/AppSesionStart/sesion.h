#ifndef SESION_H
#define SESION_H

#include <QMainWindow>
#include "wapp.h"
#include "dnewapp.h"
#include <QSystemTrayIcon>


namespace Ui {
class Sesion;
}

class Sesion : public QMainWindow
{
    Q_OBJECT
    dNewApp *windowsAnhadir;
    int itemEditarX;
    int itemEditarY;

public:
    explicit Sesion(QWidget *parent = 0);
    ~Sesion();

private:
    Ui::Sesion *ui;

public slots:
    void anhadirItem();
    void editarItem();
    void activarEditarBtn(int y,int x);
    void eliminarItem();
    void newItem(QString nameApp, QString cmdApp,int timeContador,bool persistencia);

signals:
    void initGetData(int index);
};

#endif // SESION_H
