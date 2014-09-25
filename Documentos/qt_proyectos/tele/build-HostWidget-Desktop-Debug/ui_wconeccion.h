/********************************************************************************
** Form generated from reading UI file 'wconeccion.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WCONECCION_H
#define UI_WCONECCION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wConeccion
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *wConeccion)
    {
        if (wConeccion->objectName().isEmpty())
            wConeccion->setObjectName(QStringLiteral("wConeccion"));
        wConeccion->resize(225, 27);
        horizontalLayout = new QHBoxLayout(wConeccion);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, -1, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(wConeccion);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../../../usr/share/icons/Faenza/emblems/scalable/emblem-people.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(pushButton);


        retranslateUi(wConeccion);

        QMetaObject::connectSlotsByName(wConeccion);
    } // setupUi

    void retranslateUi(QWidget *wConeccion)
    {
        wConeccion->setWindowTitle(QApplication::translate("wConeccion", "Form", 0));
        pushButton->setText(QApplication::translate("wConeccion", "Chat", 0));
    } // retranslateUi

};

namespace Ui {
    class wConeccion: public Ui_wConeccion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WCONECCION_H
