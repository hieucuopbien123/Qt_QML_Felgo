QT += widgets
TEMPLATE = lib
VERSION = 1.0.0
CONFIG += plugin release
TARGET = MyPlugin

HEADERS += \
    IPlugin.h \
    myplugin.h

SOURCES += \
    myplugin.cpp
