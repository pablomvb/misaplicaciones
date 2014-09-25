#ifndef WINFOCONECCION_H
#define WINFOCONECCION_H

#include <QWidget>

namespace Ui {
class wInfoConeccion;
}

class wInfoConeccion : public QWidget
{
    Q_OBJECT

public:
    explicit wInfoConeccion(QWidget *parent = 0);
    ~wInfoConeccion();

public slots:
    void setEstado(int estado);

private:
    Ui::wInfoConeccion *ui;
};

#endif // WINFOCONECCION_H
