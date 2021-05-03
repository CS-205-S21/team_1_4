QT += core sql
TARGET = gui
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp

LIBS += -pthread

SOURCES += ../../gtest/googletest/src/gtest-all.cc

INCLUDEPATH += ../../gtest \
 ../../gtest/googletest \
 ../../gtest/googletest/include \
 ../../gtest/googletest/include/gtest


HEADERS += ../matchmaking/matchmaker.h
SOURCES += ../matchmaking/matchmaker.cpp

HEADERS += ../databasemanager/databasemanager.h
SOURCES += ../databasemanager/databasemanager.cpp

