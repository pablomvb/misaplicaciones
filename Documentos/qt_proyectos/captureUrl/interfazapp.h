#ifndef INTERFAZAPP_H
#define INTERFAZAPP_H

#include <QObject>
#include <QList>
#include "downmanager.h"
#include "scaner.h"

class InterfazApp : public QObject
{
    Q_OBJECT
    QString urlDown;
    DownManager *appDownManager;
    Scaner *appCaptureUrl;
    QStringList listaSubItems;
    QStringList listDataSubItems;
    int contadorSubItems;
    bool subItemsMode;

public:
    explicit InterfazApp(QObject *parent = 0);
    void start();
    void startDownSubItems();

signals:

public slots:
    void estadDownManager(int e);
    void estadCaptureUrl(int e);
};

#endif // INTERFAZAPP_H
