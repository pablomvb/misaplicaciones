/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgetcontrol.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    widgetControl *wInfoControl;
    QVBoxLayout *verticalLayout;
    QLabel *nameApp;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QLabel *nameMachine;
    QLabel *ipLocal;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 195);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        wInfoControl = new widgetControl(centralWidget);
        wInfoControl->setObjectName(QStringLiteral("wInfoControl"));

        horizontalLayout->addWidget(wInfoControl);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        nameApp = new QLabel(centralWidget);
        nameApp->setObjectName(QStringLiteral("nameApp"));
        QFont font;
        font.setFamily(QStringLiteral("Roboto Condensed"));
        font.setPointSize(28);
        font.setBold(true);
        font.setWeight(75);
        nameApp->setFont(font);
        nameApp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(nameApp);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        nameMachine = new QLabel(centralWidget);
        nameMachine->setObjectName(QStringLiteral("nameMachine"));
        QFont font1;
        font1.setFamily(QStringLiteral("Roboto Condensed"));
        font1.setPointSize(22);
        font1.setBold(true);
        font1.setWeight(75);
        nameMachine->setFont(font1);
        nameMachine->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nameMachine);

        ipLocal = new QLabel(centralWidget);
        ipLocal->setObjectName(QStringLiteral("ipLocal"));
        QFont font2;
        font2.setFamily(QStringLiteral("Roboto Condensed"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        ipLocal->setFont(font2);
        ipLocal->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(ipLocal);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        nameApp->setText(QApplication::translate("MainWindow", "wHOST  ", 0));
        nameMachine->setText(QApplication::translate("MainWindow", "nameMachine", 0));
        ipLocal->setText(QApplication::translate("MainWindow", "ipLocal", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
