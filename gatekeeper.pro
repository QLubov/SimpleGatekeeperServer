#-------------------------------------------------
#
# Project created by QtCreator 2013-10-04T10:13:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gatekeeper
TEMPLATE = app
RESOURCES += run.qrc

SOURCES += main.cpp\
    xmlreader.cpp \    
    gatekeeperserver.cpp \
    gatekeeperlistener.cpp \
    endpoint.cpp \    
    logmanager.cpp \    
    mymainwindow.cpp \   
    qservermanager.cpp

HEADERS  += \    
    xmlreader.h \
    gatekeeperserver.h \
    gatekeeperlistener.h \
    endpoint.h \   
    logmanager.h \
    mymainwindow.h \   
    qservermanager.h

FORMS    += \
    mymainwindow.ui

INCLUDEPATH += D:/newh323/ptlib/include
INCLUDEPATH += D:/newh323/h323plus/include

include(actions.pri)

LIBS += -lD:/newh323/h323plus/lib/h323plusd
LIBS += -lD:/newh323/ptlib/Lib/ptlibsd
LIBS += -latlsd
LIBS += -loleaut32
