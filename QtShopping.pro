#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T16:07:48
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtShopping
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogshops.cpp \
    dialogcategories.cpp \
    dialogitems.cpp \
    dialogedititem.cpp \
    Common.cpp \
    Singleton.cpp \
    commondb.cpp

HEADERS  += mainwindow.h \
    dialogshops.h \
    dialogcategories.h \
    dialogitems.h \
    dialogedititem.h \
    Common.h \
    Common_parameters.h \
    Singleton.h \
    commondb.h

FORMS    += mainwindow.ui \
    dialogshops.ui \
    dialogcategories.ui \
    dialogitems.ui \
    dialogedititem.ui

CONFIG += c++11
CONFIG += mobility
MOBILITY = 

OTHER_FILES += \
    README.md

