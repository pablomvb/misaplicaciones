#ifndef WAPP_H
#define WAPP_H

#include <QWidget>
#include "appthread.h"
#include <QDebug>
#include <QTimer>

namespace Ui {
class wApp;
}

class wApp : public QWidget
{
    Q_OBJECT
    int index;
    int codeExit;
    int timerDuracion;
    bool run;
    bool persistencia;
    QString nameApp;
    QString cmdApp;
    AppThread *aplicacionRun;
    QTimer *timerEspera;
    QString pid;

public:
    explicit wApp(QWidget *parent = 0);
    ~wApp();
    void setData(int index, int tDuracion, QString nameApp, QString cmdApp,bool persistencia);
    int getDataDuracion();
    QString getDataNameApp();
    QString getDataCmdApp();
    bool getDataPersistencia();


public slots:
    void estadoWidget(int estado);
    void removerWidget();
    void startApp();
    void ErrorApp(int ErrorA);
    void getData(int index);
    void cambioPersistencia(bool persistencia);
    void setPID(QString pid);

private:
    Ui::wApp *ui;

signals:
    void getData(QString nameApp, QString cmdApp, int time, bool persistencia);
};

#endif // WAPP_H
