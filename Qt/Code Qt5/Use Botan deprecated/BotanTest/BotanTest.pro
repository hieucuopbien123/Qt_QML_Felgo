#-------------------------------------------------
#
# Project created by QtCreator 2012-07-23T18:19:09
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = BotanTest
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include(Botan.pri)

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += main.cpp \
    botan.cpp \
    botanwrapper.cpp

HEADERS += \
    botan.h \
    botanwrapper.h
