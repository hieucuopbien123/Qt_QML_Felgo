QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -LC:\\Qt\\Tools\\OpenSSL\\Win_x64
LIBS += -LC:\\Qt\\Tools\\OpenSSL\\Win_x64\\bin
LIBS += -llibcrypto-1_1-x64
LIBS += -llibssl-1_1-x64
INCLUDEPATH += C:\\Qt\\Tools\\OpenSSL\\Win_x64\\include

SOURCES += \
        cipher.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cipher.h
