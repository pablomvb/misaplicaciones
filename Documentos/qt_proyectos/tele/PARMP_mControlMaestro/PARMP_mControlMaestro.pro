#-------------------------------------------------
#
# Project created by QtCreator 2014-07-06T01:32:51
#
#-------------------------------------------------

QT       += widgets core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PARMP_mControlMaestro
TEMPLATE = app


SOURCES += main.cpp\
        controlmaestro.cpp \
    socketmod.cpp

HEADERS  += controlmaestro.h \
    socketmod.h

FORMS    += controlmaestro.ui \
    wequipo.ui
