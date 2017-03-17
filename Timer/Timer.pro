#-------------------------------------------------
#
# Project created by QtCreator 2017-02-02T16:06:23
#
#-------------------------------------------------
CONFIG += c++11
QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Timer
TEMPLATE = app


SOURCES += main.cpp\
        timer.cpp \
    mythread.cpp \
    db.cpp

HEADERS  += timer.h \
    mythread.h \
    db.h

FORMS    += timer.ui
