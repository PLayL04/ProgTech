QT += testlib
QT += core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

TEMPLATE = app

HEADERS += \
    ../src/estatemanager.h\
    ../src/realestate.h

SOURCES +=  \
    ../src/estatemanager.cpp\
    ../src/realestate.cpp \
    testcontroller.cpp
