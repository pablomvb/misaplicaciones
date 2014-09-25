/********************************************************************************
** Form generated from reading UI file 'winformacion.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINFORMACION_H
#define UI_WINFORMACION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wInformacion
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtIP;
    QLineEdit *txtUser;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *wInformacion)
    {
        if (wInformacion->objectName().isEmpty())
            wInformacion->setObjectName(QStringLiteral("wInformacion"));
        wInformacion->resize(318, 78);
        horizontalLayout = new QHBoxLayout(wInformacion);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(wInformacion);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(wInformacion);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        txtIP = new QLineEdit(wInformacion);
        txtIP->setObjectName(QStringLiteral("txtIP"));
        txtIP->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, txtIP);

        txtUser = new QLineEdit(wInformacion);
        txtUser->setObjectName(QStringLiteral("txtUser"));
        txtUser->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, txtUser);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer_2 = new QSpacerItem(59, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(wInformacion);

        QMetaObject::connectSlotsByName(wInformacion);
    } // setupUi

    void retranslateUi(QWidget *wInformacion)
    {
        wInformacion->setWindowTitle(QApplication::translate("wInformacion", "Form", 0));
        label->setText(QApplication::translate("wInformacion", "Ip", 0));
        label_2->setText(QApplication::translate("wInformacion", "Usuario", 0));
    } // retranslateUi

};

namespace Ui {
    class wInformacion: public Ui_wInformacion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINFORMACION_H
