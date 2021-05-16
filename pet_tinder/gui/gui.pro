#-------------------------------------------------
#
# Project created by QtCreator 2021-03-24T16:55:56
#
#-------------------------------------------------

QT += core sql
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
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


SOURCES += \
        main.cpp \
    homescreen.cpp \
    profilepage.cpp \
    petlist.cpp \
    petfinder.cpp \
    messagescreen.cpp \
    adopteeaddpet.cpp \
    preftab.cpp \
    addaccount.cpp \
    chatinfo.cpp

HEADERS += \
    homescreen.h \
    profilepage.h \
    petlist.h \
    petfinder.h \
    messagescreen.h \
    adopteeaddpet.h \
    preftab.h \
    addaccount.h \
    chatinfo.h

FORMS += \
    homescreen.ui \
    profilepage.ui \
    petlist.ui \
    petfinder.ui \
    messagescreen.ui \
    adopteeaddpet.ui \
    preftab.ui \
    addaccount.ui \
    chatinfo.ui

HEADERS += ../matchmaking/matchmaker.h
SOURCES += ../matchmaking/matchmaker.cpp
HEADERS += ../databasemanager/databasemanager.h
SOURCES += ../databasemanager/databasemanager.cpp

RESOURCES += \
    petpics_gui.qrc


