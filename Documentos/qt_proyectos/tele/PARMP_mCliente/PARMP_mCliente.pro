#-------------------------------------------------
#
# Project created by QtCreator 2014-07-05T19:18:20
#
#-------------------------------------------------

QT       += widgets core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PARMP_mCliente
TEMPLATE = app


SOURCES += main.cpp\
        cliente.cpp \
    camara.cpp \
    winfoview.cpp

HEADERS  += cliente.h \
    camara.h \
    winfoview.h

FORMS    += cliente.ui \
    winfoview.ui

RESOURCES += \
    imgFiles.qrc
