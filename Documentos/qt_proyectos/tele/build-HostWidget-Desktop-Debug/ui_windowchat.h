/********************************************************************************
** Form generated from reading UI file 'windowchat.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWCHAT_H
#define UI_WINDOWCHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_windowChat
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *windowChat)
    {
        if (windowChat->objectName().isEmpty())
            windowChat->setObjectName(QStringLiteral("windowChat"));
        windowChat->resize(400, 300);
        verticalLayout = new QVBoxLayout(windowChat);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget = new QListWidget(windowChat);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(windowChat);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(windowChat);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(windowChat);

        QMetaObject::connectSlotsByName(windowChat);
    } // setupUi

    void retranslateUi(QWidget *windowChat)
    {
        windowChat->setWindowTitle(QApplication::translate("windowChat", "Form", 0));
        pushButton->setText(QApplication::translate("windowChat", "Enviar", 0));
    } // retranslateUi

};

namespace Ui {
    class windowChat: public Ui_windowChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWCHAT_H
