/********************************************************************************
** Form generated from reading UI file 'cliente.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTE_H
#define UI_CLIENTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "winfoview.h"

QT_BEGIN_NAMESPACE

class Ui_Cliente
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    wInfoView *wFlujoTeclado;
    wInfoView *wFlujoMouse;
    wInfoView *wFlujoDisplay;
    QLineEdit *txtIp;
    QLineEdit *txtEquipo;
    wInfoView *wEstacionControl;

    void setupUi(QMainWindow *Cliente)
    {
        if (Cliente->objectName().isEmpty())
            Cliente->setObjectName(QStringLiteral("Cliente"));
        Cliente->resize(365, 174);
        Cliente->setMinimumSize(QSize(0, 0));
        Cliente->setMaximumSize(QSize(700, 16777215));
        centralWidget = new QWidget(Cliente);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(30);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(16777215, 30));
        QFont font;
        font.setFamily(QStringLiteral("Space Age"));
        font.setPointSize(22);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_7);

        wFlujoTeclado = new wInfoView(centralWidget);
        wFlujoTeclado->setObjectName(QStringLiteral("wFlujoTeclado"));

        formLayout->setWidget(5, QFormLayout::FieldRole, wFlujoTeclado);

        wFlujoMouse = new wInfoView(centralWidget);
        wFlujoMouse->setObjectName(QStringLiteral("wFlujoMouse"));

        formLayout->setWidget(4, QFormLayout::FieldRole, wFlujoMouse);

        wFlujoDisplay = new wInfoView(centralWidget);
        wFlujoDisplay->setObjectName(QStringLiteral("wFlujoDisplay"));

        formLayout->setWidget(3, QFormLayout::FieldRole, wFlujoDisplay);

        txtIp = new QLineEdit(centralWidget);
        txtIp->setObjectName(QStringLiteral("txtIp"));
        txtIp->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, txtIp);

        txtEquipo = new QLineEdit(centralWidget);
        txtEquipo->setObjectName(QStringLiteral("txtEquipo"));
        txtEquipo->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, txtEquipo);

        wEstacionControl = new wInfoView(centralWidget);
        wEstacionControl->setObjectName(QStringLiteral("wEstacionControl"));

        formLayout->setWidget(2, QFormLayout::FieldRole, wEstacionControl);


        verticalLayout->addLayout(formLayout);

        Cliente->setCentralWidget(centralWidget);

        retranslateUi(Cliente);

        QMetaObject::connectSlotsByName(Cliente);
    } // setupUi

    void retranslateUi(QMainWindow *Cliente)
    {
        Cliente->setWindowTitle(QApplication::translate("Cliente", "Cliente", 0));
        label->setText(QApplication::translate("Cliente", "Host  ", 0));
        label_2->setText(QApplication::translate("Cliente", "Ip", 0));
        label_3->setText(QApplication::translate("Cliente", "Equipo", 0));
        label_4->setText(QApplication::translate("Cliente", "Estacion de Control", 0));
        label_5->setText(QApplication::translate("Cliente", "Pantalla", 0));
        label_6->setText(QApplication::translate("Cliente", "Mouse", 0));
        label_7->setText(QApplication::translate("Cliente", "Teclado", 0));
    } // retranslateUi

};

namespace Ui {
    class Cliente: public Ui_Cliente {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTE_H
