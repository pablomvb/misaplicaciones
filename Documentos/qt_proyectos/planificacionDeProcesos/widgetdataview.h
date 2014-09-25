#ifndef WIDGETDATAVIEW_H
#define WIDGETDATAVIEW_H

#include <QWidget>
#include <QDebug>
#include <QList>

namespace Ui {
class widgetDataView;
}

class widgetDataView : public QWidget
{
    Q_OBJECT
    int metodo;
    int qRoundRobin;
    int menor1;

public:
    explicit widgetDataView(QWidget *parent = 0);
    ~widgetDataView();

public slots:
    void setMetodo(int metodo);
    void getData(QStringList lista);
    void resetTbl();
    void runMetodo();
    void autoRunMetodo();
    void setQtime(int i);

private:
    Ui::widgetDataView *ui;
    void runMetodoFCFS(int nDatos);
    void runMetodoSJF(int nDatos);
    void runMetodoBasadoEnPrioridades(int nDatos);
    void runMetodoRoundRobin(int nDatos);
    void runMetodoMulticolas(int nDatos);

signals:
    void getResetIdProceso();
    void autoCalculo();

};

#endif // WIDGETDATAVIEW_H
