#include "temas.h"

Temas::Temas(QObject *parent) :
    QObject(parent)
{
}

QString Temas::boton_hover_TaskBar()
{
    return"QPushButton:hover {color: \"#00C8FF\"}";
}

QString Temas::boton_press_TaskBar()
{
    return"color:\"#FFFFFF\"";
}
