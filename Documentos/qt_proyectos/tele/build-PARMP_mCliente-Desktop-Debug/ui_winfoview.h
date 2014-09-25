/********************************************************************************
** Form generated from reading UI file 'winfoview.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINFOVIEW_H
#define UI_WINFOVIEW_H

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

class Ui_wInfoView
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *infoColor;
    QLabel *lblEstado;

    void setupUi(QWidget *wInfoView)
    {
        if (wInfoView->objectName().isEmpty())
            wInfoView->setObjectName(QStringLiteral("wInfoView"));
        wInfoView->resize(374, 16);
        horizontalLayout = new QHBoxLayout(wInfoView);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        infoColor = new QPushButton(wInfoView);
        infoColor->setObjectName(QStringLiteral("infoColor"));
        infoColor->setMaximumSize(QSize(10, 10));
        infoColor->setStyleSheet(QLatin1String("background-color: rgb(116, 116, 116);\n"
"border-style: outset;\n"
"border-width: 1px;\n"
"border-radius: 2px;\n"
"border-color: rgb(34, 34, 34);"));

        horizontalLayout->addWidget(infoColor);

        lblEstado = new QLabel(wInfoView);
        lblEstado->setObjectName(QStringLiteral("lblEstado"));

        horizontalLayout->addWidget(lblEstado);


        retranslateUi(wInfoView);

        QMetaObject::connectSlotsByName(wInfoView);
    } // setupUi

    void retranslateUi(QWidget *wInfoView)
    {
        wInfoView->setWindowTitle(QApplication::translate("wInfoView", "Form", 0));
        infoColor->setText(QString());
        lblEstado->setText(QApplication::translate("wInfoView", "txt_Estado", 0));
    } // retranslateUi

};

namespace Ui {
    class wInfoView: public Ui_wInfoView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINFOVIEW_H
