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
    Common.cpp \
    Singleton.cpp \
    Database/shopdb.cpp \
    Database/commondb.cpp \
    Database/categorydb.cpp \
    Database/itemdb.cpp \
    Dialog_Input_New/dialog_input_new_category.cpp \
    Dialog_Input_New/dialog_input_new_shop.cpp \
    common_struct_data.cpp \ 
    Dialog_Input_New/dialog_input_new_item.cpp \
    Database/cashdb.cpp \
    dialogcash.cpp \
    dialogpaymentcashbox.cpp \
    Database/historydb.cpp

HEADERS  += mainwindow.h \
    dialogshops.h \
    dialogcategories.h \
    dialogitems.h \
    Common.h \
    Common_parameters.h \
    Singleton.h \
    Database/shopdb.h \
    Database/commondb.h \
    Database/categorydb.h \
    Database/itemdb.h \
    Dialog_Input_New/dialog_input_new_category.h \
    Dialog_Input_New/dialog_input_new_shop.h \
    common_struct_data.h \
    Dialog_Input_New/dialog_input_new_item.h \
    Database/cashdb.h \
    dialogcash.h \
    dialogpaymentcashbox.h \
    dialogpaymentcashbox.h \
    Database/historydb.h

FORMS    += mainwindow.ui \
    dialogshops.ui \
    dialogcategories.ui \
    dialogitems.ui \
    Dialog_Input_New/dialog_input_new_category.ui \
    Dialog_Input_New/dialog_input_new_shop.ui \
    Dialog_Input_New/dialog_input_new_item.ui \
    dialogcash.ui \
    dialogpaymentcashbox.ui \
    dialogpaymentcashbox.ui

CONFIG += c++11
CONFIG += mobility
MOBILITY = 

OTHER_FILES += \
    README.md

