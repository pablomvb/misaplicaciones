#ifndef DOWNMANAGER_H
#define DOWNMANAGER_H

#include <QObject>
#include <QSignalSpy>
#include <QTime>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProgressBar>

class SignalWait
{
    QSignalSpy m_SignalSpy;

public:

    SignalWait(QObject *object, const char *signal) : m_SignalSpy(object, signal) {}

    bool Wait(const int segTimeout)
    {

        QTime Timer(0,0,segTimeout,0);

        Timer.start();

        while(m_SignalSpy.isEmpty() == true && Timer.elapsed() < segTimeout)
        {
            QCoreApplication::processEvents();
        }

        return (!m_SignalSpy.isEmpty());
    }
};

class DownManager : public QObject
{
    Q_OBJECT

    QUrl urlDireccion;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QByteArray data;
    QProgressBar* barDownload;
    //SignalWait* signal;

    int estado;

public:
    explicit DownManager(QObject *parent = 0);
    int urlDownload(QString url,int timeSeg=60);
    QByteArray dataDownload(){return data;}

signals:
    void iniciarDescargar();
    void fDown();
    void out(qint64 d1,qint64 d2);

public slots:
    void finDownFile();
    void leerDownFile();
    void downDataUrl();
    void updateProgressBar(qint64 d1,qint64 d2);
};

#endif // DOWNMANAGER_H



//class SignalWait
//{

//QSignalSpy m_SignalSpy;

//public:

//SignalWait(QObject *object, const char *signal) : m_SignalSpy(object, signal) {}

//bool Wait(const int msTimeout)
//{
//    QTime Timer(0,0,0,msTimeout);

//    Timer.start();

//    while(m_SignalSpy.isEmpty() == true && Timer.elapsed() < msTimeout)
//    {
//        QCoreApplication::processEvents();
//    }

//    return (!m_SignalSpy.isEmpty());
//}
//};
