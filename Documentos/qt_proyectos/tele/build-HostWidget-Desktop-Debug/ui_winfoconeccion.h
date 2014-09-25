/********************************************************************************
** Form generated from reading UI file 'winfoconeccion.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINFOCONECCION_H
#define UI_WINFOCONECCION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wInfoConeccion
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *vEstadoColor;
    QLabel *vEstadoDescripcion;

    void setupUi(QWidget *wInfoConeccion)
    {
        if (wInfoConeccion->objectName().isEmpty())
            wInfoConeccion->setObjectName(QStringLiteral("wInfoConeccion"));
        wInfoConeccion->resize(400, 20);
        horizontalLayout = new QHBoxLayout(wInfoConeccion);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(17, 4, -1, 4);
        vEstadoColor = new QPushButton(wInfoConeccion);
        vEstadoColor->setObjectName(QStringLiteral("vEstadoColor"));
        vEstadoColor->setMinimumSize(QSize(12, 12));
        vEstadoColor->setMaximumSize(QSize(12, 10));

        horizontalLayout->addWidget(vEstadoColor);

        vEstadoDescripcion = new QLabel(wInfoConeccion);
        vEstadoDescripcion->setObjectName(QStringLiteral("vEstadoDescripcion"));

        horizontalLayout->addWidget(vEstadoDescripcion);


        retranslateUi(wInfoConeccion);

        QMetaObject::connectSlotsByName(wInfoConeccion);
    } // setupUi

    void retranslateUi(QWidget *wInfoConeccion)
    {
        wInfoConeccion->setWindowTitle(QApplication::translate("wInfoConeccion", "Form", 0));
        vEstadoColor->setText(QString());
        vEstadoDescripcion->setText(QApplication::translate("wInfoConeccion", "_estado", 0));
    } // retranslateUi

};

namespace Ui {
    class wInfoConeccion: public Ui_wInfoConeccion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINFOCONECCION_H
