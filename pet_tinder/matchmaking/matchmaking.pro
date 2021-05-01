QT = core sql
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    matchmaker.cpp

HEADERS += \
    matchmaker.h

HEADERS += ../databasemanager/databasemanager.h
SOURCES += ../databasemanager/databasemanager.cpp
