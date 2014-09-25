#ifndef TEMAS_H
#define TEMAS_H

#include <QObject>

class Temas : public QObject
{
    Q_OBJECT
public:
    explicit Temas(QObject *parent = 0);
    QString boton_hover_TaskBar();
    QString boton_press_TaskBar();

signals:

public slots:

};

#endif // TEMAS_H
