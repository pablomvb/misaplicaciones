#ifndef WINDOWCHAT_H
#define WINDOWCHAT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class windowChat;
}

class windowChat : public QWidget
{
    Q_OBJECT
    QTcpSocket* socketChat;
    int tEspera;
    int chatConectado;

public:
    explicit windowChat(QWidget *parent = 0);
    ~windowChat();
    int setConectar(QString ip, int puerto);
    void setTespera(int t){ tEspera = t;}

public slots:
    void leerMensaje();
    void enviarMensaje();

private:
    Ui::windowChat *ui;
};

#endif // WINDOWCHAT_H
