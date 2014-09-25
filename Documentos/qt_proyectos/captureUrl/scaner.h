#ifndef SCANER_H
#define SCANER_H

#include <QObject>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class Scaner : public QObject
{
    Q_OBJECT
    QString idScript;
    QString nameValue;
    QString stateValue;
    QStringList listSubItemValue;
    QStringList listDataSubItemValue;
    QStringList listUrlsSubItemValue;
    int contadorDataSubItems;
    int contadorInversoSubItems;

    QStringList dataAnalisis;
    QFile fileScript;
    int contador;
    QTextStream *input;
    QString dataOutCreateScript;

    bool initProcessSubItems;

public:
    explicit Scaner(QObject *parent = 0);
    void setIdScript(QString id);
    void setDataRAW(QByteArray data);
    int loadScript();
    void createScript();
    bool validar(QString clave,QString patronExtracion, QString modo);
    void cmdScript(bool modeListSubItem = false);
    bool preguntarSiNo(int nQuestion = 0);
    QStringList getLisSubItems();
    void setLisDataSubItems(QStringList data);

signals:
    void estado(int e);

public slots:
    void startProcessSubItems();

};

#endif // SCANER_H
