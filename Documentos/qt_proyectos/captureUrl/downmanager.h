#ifndef DOWNMANAGER_H
#define DOWNMANAGER_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DownManager : public QObject
{
    Q_OBJECT
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QByteArray data;
    QString urlRedirection;

public:
    explicit DownManager(QObject *parent = 0);
    QByteArray getData(){return data;}
    QString getUrlRedirection(){return urlRedirection;}

signals:
    void estado(int e);

public slots:
    void downFile(QString urlFile);
    void finDownFile();
    void leerDownFile();
};

#endif // DOWNMANAGER_H
