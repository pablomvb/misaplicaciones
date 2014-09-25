#-------------------------------------------------
#
# Project created by QtCreator 2014-09-02T22:38:09
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TerminalRemotaServidor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    sesion.cpp \
    comando.cpp

HEADERS += \
    sesion.h \
    comando.h
