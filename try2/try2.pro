#deisigned by liyu--V1.0


QT       += core gui
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


CONFIG += c++11


DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    dialog.cpp \
    main.cpp \
    qcustomplot.cpp \
    widget2.cpp \
    windows_out.cpp


HEADERS += \
    dialog.h \
    qcustomplot.h \
    widget2.h \
    windows_out.h




FORMS += \
    dialog.ui \
    widget2.ui \
    windows_out.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    photo.qrc
