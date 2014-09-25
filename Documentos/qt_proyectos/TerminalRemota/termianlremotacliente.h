#ifndef TERMIANLREMOTACLIENTE_H
#define TERMIANLREMOTACLIENTE_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class TermianlRemotaCliente;
}

class TermianlRemotaCliente : public QMainWindow
{
    Q_OBJECT

    QTcpSocket* cliente;

public:
    explicit TermianlRemotaCliente(QWidget *parent = 0);
    ~TermianlRemotaCliente();

private:
    Ui::TermianlRemotaCliente *ui;

public slots:
    void conectarCliente();
    void desconectarCliente();
    void enviarComando();
    void leerStdout();
};

#endif // TERMIANLREMOTACLIENTE_H
