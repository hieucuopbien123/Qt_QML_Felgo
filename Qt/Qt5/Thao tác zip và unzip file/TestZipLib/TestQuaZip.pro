QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "B:\\Qt\\newGeneration\\TestQuaZip\\include"
LIBS += "B:\\Qt\\newGeneration\\TestQuaZip\\libs\\libz.a"
LIBS += "B:\\Qt\\newGeneration\\TestQuaZip\\libs\\zlib1.dll"
LIBS += "B:\\Qt\\newGeneration\\TestQuaZip\\libs\\libz.dll.a"

SOURCES += \
        main.cpp \
        zip.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    zipreader.h \
    zipwriter.h
