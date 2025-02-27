QT       += core gui
QT       += core
QT       += network
QT       += core gui network
QT       += charts
QT       += opengl
QT       += gui
QT       += concurrent
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HotPlot.cpp \
    qcustomplot.cpp \
    main.cpp \
    mainwindow.cpp \
    udpconnect.cpp \
    config.cpp

HEADERS += \
    HotPlot.h \
    qcustomplot.h \
    udpconnect.h \
    mainwindow.h \
    CirQueue.h \
    config.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    config.qrc

FORMS += \
    mainwindow.ui
