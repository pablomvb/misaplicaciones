#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = 0);
    void run();
    QTcpServer* serverSocket;
    QTcpSocket* inputVisor;

signals:
    void data(QString d);
    void clear();

public slots:
    void read();
    void newConection();
    void lostConection();
};

#endif // SERVER_H
