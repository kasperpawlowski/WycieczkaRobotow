#-------------------------------------------------
#
# Project created by QtCreator 2019-02-20T22:33:32
#
#-------------------------------------------------

QT       += core gui \
            remoteobjects

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WycieczkaRobotow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    common/basictypes.cpp \
    formationkeypad.cpp \
    keypadpushbutton.cpp \
    situationscene.cpp \
    scratchpad.cpp \
    scratchpadcontroller.cpp \
    simulationinterface.cpp \
    simulationcontroller.cpp \
    common/point.cpp

HEADERS += \
        mainwindow.h \
    common/basictypes.h \
    formationkeypad.h \
    keypadpushbutton.h \
    situationscene.h \
    scratchpad.h \
    scratchpadcontroller.h \
    simulationinterface.h \
    common/rep_basesimulationinterface_source.h \
    simulationcontroller.h \
    common/filesgenerator.h \
    common/point.h \
    common/simulationstarter.h

FORMS += \
        mainwindow.ui

REPC_SOURCE = common/basesimulationinterface.rep

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TARGET = WycieczkaRobotow
Release:DESTDIR = ..\result
Debug:DESTDIR   = ..\result
