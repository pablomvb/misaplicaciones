#ifndef COMANDO_H
#define COMANDO_H

#include <QThread>
#include <QProcess>

class Comando : public QThread
{
    Q_OBJECT
public:
    explicit Comando(QObject *parent = 0);

signals:

public slots:

};

#endif // COMANDO_H
