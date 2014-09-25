#ifndef CONTROLMAESTRO_H
#define CONTROLMAESTRO_H

#include <QMainWindow>
#include <QTcpSocket>
//#include <QTcpServer>
#include <socketmod.h>

namespace Ui {
class ControlMaestro;
}

class ControlMaestro : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlMaestro(QWidget *parent = 0);
    ~ControlMaestro();

public slots:
    void eliminarItem();
    void anhadirItem(QString ipEquipoRemoto);
    void escanearRedLocal();
    void debugModo(QString m);
    void debugStatusBar(QString addTxt);
    void resolverIpLocal();
    void listarEquipos();
    void testLocalHost();

private:
    Ui::ControlMaestro *ui;
    QTcpSocket* socketControl;
    int contadorPuertos;
    int puertoControl;
    QString ipControlLocal;
    QList<socketMod*> equipoLista;

};

#endif // CONTROLMAESTRO_H
