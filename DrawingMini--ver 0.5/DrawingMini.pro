QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# 程设大作业  未名画板
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawingtoolbar.cpp \
    drawingtools.cpp \
    drawingwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    shapes.cpp \
    startwidget.cpp

HEADERS += \
    drawingtoolbar.h \
    drawingtools.h \
    drawingwidget.h \
    mainwindow.h \
    shapes.h \
    startwidget.h

FORMS += \
    drawingwidget.ui \
    mainwindow.ui \
    startwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc
