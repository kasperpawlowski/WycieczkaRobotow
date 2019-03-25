QT -= gui
QT += remoteobjects

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    ../common/basictypes.cpp \
    ../common/point.cpp \
    ../common/position.cpp \
    ../common/commoninterfaceuser.cpp \
    ../common/basesimulation.cpp \
    ../common/baserobot.cpp \
    ../common/robotsmanager.cpp \
    followtheleadersimulation.cpp \
    leaderrobot.cpp \
    followerrobot.cpp \
    twowheelsrobot.cpp \
    radiodevice.cpp

HEADERS += \
    ../common/rep_basesimulationinterface_replica.h \
    ../common/basictypes.h \
    ../common/point.h \
    ../common/position.h \
    ../common/simulationstarter.h \
    ../common/commoninterfaceuser.h \
    ../common/basesimulation.h \
    ../common/baserobot.h \
    ../common/robotsmanager.h \
    ../common/filesgenerator.h \
    followtheleadersimulation.h \
    leaderrobot.h \
    followerrobot.h \
    twowheelsrobot.h \
    radiodevice.h \
    basicsensor.h

REPC_REPLICA = ../common/basesimulationinterface.rep

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TARGET = Simulation
Release:DESTDIR = ..\..\result
Debug:DESTDIR   = ..\..\result
