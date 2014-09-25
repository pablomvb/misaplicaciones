#ifndef SESIONMANA_H
#define SESIONMANA_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class SesionMana;
}

class SesionMana : public QMainWindow
{
    Q_OBJECT

    QTcpSocket* cliente;

public:
    explicit SesionMana(QWidget *parent = 0);
    void actualizarTabla();
    void loadHeaderTable();
    ~SesionMana();

public slots:
    void clienteDesconectado();
    void enviarDatos(QByteArray datos);
    void shell();
    void newDatosTabla(QStringList listaAplicaciones);

private:
    Ui::SesionMana *ui;
};

#endif // SESIONMANA_H
