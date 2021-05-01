TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
    databasemanager.cpp \
    main.cpp

HEADERS += \
    databasemanager.h

DISTFILES += \
    build_tables.sql
    drop_tables.sql
    00_build_db/adoptee.csv
    00_build_db/adopter.csv
    00_build_db/likedPet.csv
    00_build_db/messages.csv
    00_build_db/pet.csv

