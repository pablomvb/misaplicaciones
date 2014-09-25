#ifndef WIDGETCONTROL_H
#define WIDGETCONTROL_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class widgetControl;
}

class widgetControl : public QWidget
{
    Q_OBJECT
    QTcpSocket* socketControl;
    QString ipLocal;
    int puertoLocal;
    QString ipR;
    QString nameMachine;
    QString oS;
    int puertoR;
    int comando;

public:
    explicit widgetControl(QWidget *parent = 0);
    ~widgetControl();
    void startControl();
    void stopControl();
    void initWindow();
    void setData(int puerto, QString ip, QString name, QString oS);
    bool contarAdminTool(QString ip, int port);

public slots:
    void shellControl();
    void clear();

private:
    Ui::widgetControl *ui;

signals:
    void disconecControl();
};

#endif // WIDGETCONTROL_H
