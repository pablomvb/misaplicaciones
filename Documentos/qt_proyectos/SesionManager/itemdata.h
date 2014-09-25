#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <QWidget>

namespace Ui {
class itemData;
}

class itemData : public QWidget
{
    Q_OBJECT
    QString comando;

public:
    explicit itemData(QWidget *parent = 0);
    ~itemData();

public slots:
    void nuevaAplicacion();
    void guardarDatos();

private:
    Ui::itemData *ui;

    void editable(bool modo);

signals:
    void getDatosAplicacion(QByteArray datosAplicacion);
};

#endif // ITEMDATA_H
