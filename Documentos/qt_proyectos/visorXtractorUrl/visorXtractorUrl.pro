#-------------------------------------------------
#
# Project created by QtCreator 2014-08-09T18:05:13
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visorXtractorUrl
TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    gui.cpp

HEADERS  += \
    server.h \
    gui.h

FORMS    += \
    gui.ui
