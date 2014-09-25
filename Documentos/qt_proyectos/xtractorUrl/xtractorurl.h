#ifndef XTRACTORURL_H
#define XTRACTORURL_H

#include <QObject>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpSocket>

class XtractorUrl : public QObject
{
    Q_OBJECT
    QTextStream* input;
    QStringList arg;
    bool modeCreateScript;
    bool modeAnlisisSubItems;
    QString errorBuffer;
    bool continuarEjecucion;

    QStringList scriptList;
    QString scriptSelect;
    bool scriptSave;
    QStringList scriptSelectI;
    QFile scriptFile;

    QFile informe;
    int informeContadorSaveData;
    int informeContadorSaveData2;
    bool informeOpen;
    QStringList saveDataFile;
    QString itemName;                   // name
    QString itemState;                  // state
    QStringList itemListSubItems;       // subItems
    int itemContadorSubItemsSelect;
    int numUrlsSubItems;
    int numUrlsSubItems_UrlSelect;
    //QStringList itemListSubItemsUrls;   // url's subItems

    QTcpSocket* visor;
    bool visorOut;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QString urlRedirection;

    QString data;
    QStringList dataAnalisis;
    int contadorIteracionData;

    bool analisiModoUrlsSubItems;


public:
    explicit XtractorUrl(QObject *parent = 0);
    void start();
    QString read();
    void write(QString label, int widgetVisor);
    bool analisisScript(QString nameScript);
    bool analisis(QString script,int idBuffer);
    bool analisisModoCreateScript(QString label,int idBufer);
    QString addScriptCmd(bool listSubItem = false);
    bool siNO(QString label);
    void analisisError(bool output, int buffer);
    void informeAddDato(QString dato);
    void openForWrite_informe();
    QString decodUrl(QString urlCod);

signals:
    void mensajero(int estado);
    void setUrl(QString url);
    void initAnalisis();
    void initAnalisisSubItems();
    void downSubItem();

public slots:
    void downDataUrl(QString url);
    void finDownFile();
    void leerDownFile();
    void disableVisor();

    void estado(int estado);

    void analisis();
    void analisisSubItems();
    void downSubItems();

};

#endif // XTRACTORURL_H
