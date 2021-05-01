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

HEADERS += ../gui/homescreen.h
SOURCES += ../gui/homescreen.cpp

HEADERS += ../gui/petlist.h
SOURCES += ../gui/petlist.cpp

HEADERS += ../gui/profilepage.h
SOURCES += ../gui/profilepage.cpp

HEADERS += ../gui/screen.h
SOURCES += ../gui/screen.cpp
