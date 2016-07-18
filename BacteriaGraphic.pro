#-------------------------------------------------
#
# Project created by QtCreator 2016-07-17T14:41:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BacteriaGraphic
TEMPLATE = app


SOURCES += main.cpp\
        MainControl.cpp \
    bacteria.cpp \
    bacteriaanimation.cpp \
    BacteriaSystem.cpp \
    PlotGraph.cpp

HEADERS  += MainControl.h \
    bacteria.h \
    bacteriaanimation.h \
    BacteriaSystem.h \
    PlotGraph.h

FORMS    += maincontrol.ui
