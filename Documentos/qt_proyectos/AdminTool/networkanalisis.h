#ifndef NETWORKANALISIS_H
#define NETWORKANALISIS_H

#include <QWidget>
#include <QProcess>
#include <QTcpSocket>

namespace Ui {
class networkAnalisis;
}

class networkAnalisis : public QWidget
{
    Q_OBJECT
    int modo;
    int contador;
    QStringList probarIps;
    QStringList IpsValidas;
    QString infoNetwork;
    int puertoLocal;
    QProcess* cmdPing;
    QTcpSocket* socketEscaner;
    float barra;

public:
    explicit networkAnalisis(QWidget *parent = 0);
    ~networkAnalisis();
    int cargarConfiguracion();
    void initScan();
    void conectarAdminTool();

private slots:
    void pingIp();
    void pingIpPasoDos();

private:
    Ui::networkAnalisis *ui;
    int obtenerIpLocal();

signals:
    void exitProgram();
};

#endif // NETWORKANALISIS_H
