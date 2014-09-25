#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T02:24:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = planificacionDeProcesos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widgetadddata.cpp \
    widgetdataview.cpp \
    widgetselecionmetodo.cpp

HEADERS  += mainwindow.h \
    widgetadddata.h \
    widgetdataview.h \
    widgetselecionmetodo.h

FORMS    += mainwindow.ui \
    widgetadddata.ui \
    widgetdataview.ui \
    widgetselecionmetodo.ui
