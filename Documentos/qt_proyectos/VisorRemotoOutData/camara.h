#ifndef CAMARA_H
#define CAMARA_H

#include <QObject>
#include <QPixmap>
#include <QScreen>
#include <QTimer>
#include <QTcpSocket>
#include <QHostAddress>

class Camara : public QObject
{
    Q_OBJECT

private:
    QScreen* display;
    QTimer* click;
    int framesXsegundo;
    QTcpSocket* socketUdpStreamDisplay;
    QPixmap* screenshot;
    QHostAddress ipDestino;
    int portDestino;

public:
    explicit Camara(QObject *parent = 0);
    QPixmap* getScreen();
    void setFrames(int f=30);
    void iniciarCaptura(QHostAddress ipBroadcast, int port);
    void detenerCaptura();
    void setIpAndPort(QString ipBroadcast, int port);

signals:
    void sendFrame(QPixmap* frame);

public slots:
    void capturarAndSend();

//private slots:
    void stream();

};

#endif // CAMARA_H
