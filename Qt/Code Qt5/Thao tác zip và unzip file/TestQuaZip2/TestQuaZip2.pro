QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QUAZIPCODEDIR = "B:\\Qt\\newGeneration/TestQuaZip/libs/"

win32 {
    LIBS += -LB:\\Qt\\newGeneration/TestQuaZip/libs
}
INCLUDEPATH += "B:\\Qt\\newGeneration\\TestQuaZip\\include"
LIBS += "$${QUAZIPCODEDIR}/libquazipd.a"#đường dẫn nên phải dùng 2 cái $$
LIBS += "B:\\Qt\\newGeneration/TestQuaZip/libs/libz.a"
LIBS += "B:\\Qt\\newGeneration/TestQuaZip/libs/libz.dll.a"
LIBS += "B:\\Qt\\newGeneration/TestQuaZip/libs/quazipd.dll"
LIBS += "B:\\Qt\\newGeneration/TestQuaZip/libs/zlib1.dll"

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    include/quazip.pro

DISTFILES += \
    include/quazip.pri \
    include/quazip.sln \
    include/quazip.vcproj \
    include/quazip.vcxproj \
    include/quazip.vcxproj.filters \
    include/run_moc.bat

HEADERS += \
    include/JlCompress.h \
    include/crc32.h \
    include/crypt.h \
    include/deflate.h \
    include/gzguts.h \
    include/inffast.h \
    include/inffixed.h \
    include/inflate.h \
    include/inftrees.h \
    include/ioapi.h \
    include/quaadler32.h \
    include/quachecksum32.h \
    include/quacrc32.h \
    include/quagzipfile.h \
    include/quaziodevice.h \
    include/quazip.h \
    include/quazip_global.h \
    include/quazipdir.h \
    include/quazipfile.h \
    include/quazipfileinfo.h \
    include/quazipnewinfo.h \
    include/trees.h \
    include/unzip.h \
    include/zconf.h \
    include/zip.h \
    include/zlib.h \
    include/zutil.h
