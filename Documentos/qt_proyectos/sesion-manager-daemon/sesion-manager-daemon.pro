#-------------------------------------------------
#
# Project created by QtCreator 2014-08-26T17:16:30
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = sesion-manager-daemon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    sesion.cpp \
    aplicacion.cpp

HEADERS += \
    sesion.h \
    aplicacion.h
