QT += core
QT -= gui

CONFIG += c++11

TARGET = testprocedure
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test.cpp

HEADERS += \
    test.h
