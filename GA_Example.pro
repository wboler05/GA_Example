#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T16:26:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GA_Example
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

CONFIG += c++14
CONFIG += -fopenmp

QMAKE_CXXFLAGS_RELEASE -= -O0
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

INCLUDEPATH += GA

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    GA/ga.cpp \
    GA/particle.cpp \
    GA/fitness.cpp \
    randomnumber.cpp

HEADERS += \
        mainwindow.h \
    GA/ga.h \
    GA/particle.h \
    GA/fitness.h \
    randomnumber.h

FORMS += \
        mainwindow.ui
