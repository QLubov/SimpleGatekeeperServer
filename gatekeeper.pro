#-------------------------------------------------
#
# Project created by QtCreator 2013-10-04T10:13:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gatekeeper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlreader.cpp \
    logwindow.cpp \
    grqcommand.cpp \
    gcfcommand.cpp \
    commandfactory.cpp \
    command.cpp \
    actionmanager.cpp \
    gatekeeperserver.cpp \
    gatekeeperlistener.cpp \
    endpoint.cpp \
    grjcommand.cpp \
    qserverthread.cpp \
    logmanager.cpp \
    rrqcommand.cpp \
    rcfcommand.cpp

HEADERS  += mainwindow.h \
    logwindow.h \
    grqcommand.h \
    gcfcommand.h \
    commandfactory.h \
    command.h \
    xmlreader.h \
    actionmanager.h \
    gatekeeperserver.h \
    gatekeeperlistener.h \
    endpoint.h \
    grjcommand.h \
    qserverthread.h \
    logmanager.h \
    rrqcommand.h \
    rcfcommand.h

FORMS    += mainwindow.ui \
    logwindow.ui

INCLUDEPATH += D:/newh323/ptlib/include
INCLUDEPATH += D:/newh323/h323plus/include


LIBS += -lD:/newh323/h323plus/lib/h323plusd
LIBS += -lD:/newh323/ptlib/Lib/ptlibsd
LIBS += -latlsd
LIBS += -loleaut32
