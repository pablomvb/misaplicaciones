#ifndef DONWLOADMANAGER_H
#define DONWLOADMANAGER_H

#include <QWidget>
//#include <QObject>
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

namespace Ui {
class DonwloadManager;
}

class DonwloadManager : public QWidget
{
    Q_OBJECT
    QUrl urlDireccion;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QByteArray dataRAW;
    QProgressBar* barDownload;
    //SignalWait* signal;

    int estado;

public:
    explicit DonwloadManager(QWidget *parent = 0);
    ~DonwloadManager();
    int urlDownload(QString url,int timeSeg=60);
    QByteArray dataDownload(){return dataRAW;}

private:
    Ui::DonwloadManager *ui;

signals:
    void iniciarDescargar();
    void fDown();
    void out(qint64 d1,qint64 d2);

private slots:
    void finDownFile();
    void leerDownFile();
    void downDataUrl();
    void updateProgressBar(qint64 d1,qint64 d2);
};

#endif // DONWLOADMANAGER_H
