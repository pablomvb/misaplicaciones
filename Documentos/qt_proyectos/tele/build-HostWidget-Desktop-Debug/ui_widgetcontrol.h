/********************************************************************************
** Form generated from reading UI file 'widgetcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETCONTROL_H
#define UI_WIDGETCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "winfoconeccion.h"

QT_BEGIN_NAMESPACE

class Ui_widgetControl
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    wInfoConeccion *wInfoAmin;
    QFrame *line;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;

    void setupUi(QWidget *widgetControl)
    {
        if (widgetControl->objectName().isEmpty())
            widgetControl->setObjectName(QStringLiteral("widgetControl"));
        widgetControl->setWindowModality(Qt::NonModal);
        widgetControl->resize(200, 311);
        widgetControl->setMaximumSize(QSize(250, 16777215));
        horizontalLayout_2 = new QHBoxLayout(widgetControl);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 5, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widgetControl);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Roboto"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        wInfoAmin = new wInfoConeccion(widgetControl);
        wInfoAmin->setObjectName(QStringLiteral("wInfoAmin"));

        horizontalLayout->addWidget(wInfoAmin);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(widgetControl);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        line_2 = new QFrame(widgetControl);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);


        retranslateUi(widgetControl);

        QMetaObject::connectSlotsByName(widgetControl);
    } // setupUi

    void retranslateUi(QWidget *widgetControl)
    {
        widgetControl->setWindowTitle(QApplication::translate("widgetControl", "Form", 0));
        label->setText(QApplication::translate("widgetControl", "nombreAdmin ", 0));
    } // retranslateUi

};

namespace Ui {
    class widgetControl: public Ui_widgetControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETCONTROL_H
