#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T13:10:25
#
#-------------------------------------------------

QT       += core gui webkitwidgets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puenktlichkeitsassistent1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newroutedialog.cpp \
    route.cpp \
    network.cpp \
    aboutdialog.cpp \
    parsejson.cpp


HEADERS  += mainwindow.h \
    newroutedialog.h \
    route.h \
    network.h \
    aboutdialog.h \
    parsejson.h

FORMS    += mainwindow.ui \
    newroutedialog.ui \
    aboutdialog.ui

RESOURCES += \
    myresource.qrc

LIBS += ws2_32.lib

LIBS += -L$$PWD/3rdParty/openssl-1.0.1p.64/lib -lssleay32
LIBS += -L$$PWD/3rdParty/openssl-1.0.1p.64/lib -llibeay32

INCLUDEPATH += $$PWD/3rdParty/openssl-1.0.1p.64/include
INCLUDEPATH += $$PWD/3rdParty/rapidjson

RC_ICONS = myicon.ico
