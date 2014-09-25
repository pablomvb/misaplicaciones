#ifndef WIDGETADDDATA_H
#define WIDGETADDDATA_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class widgetAddData;
}

class widgetAddData : public QWidget
{
    Q_OBJECT
    int metodo;
    int nProceso;

public:
    explicit widgetAddData(QWidget *parent = 0);
    ~widgetAddData();
    void setIdProceso();

public slots:
    void setMetodo(int metodo);
    void btnAdd();
    void setResetIdProceso();
    void qTime();
    void qTime(int q);

private:
    Ui::widgetAddData *ui;

signals:
    void getData(QStringList items);
    void getQtimeCiclo(int q);
};

#endif // WIDGETADDDATA_H
