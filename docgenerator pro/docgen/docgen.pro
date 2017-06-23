#-------------------------------------------------
#
# Project created by QtCreator 2017-06-22T11:31:48
#
#-------------------------------------------------

QT       += core gui
QT      +=xml
QT  +=printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = docgen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlgen.cpp \
    xmlwriter.cpp

HEADERS  += mainwindow.h \
    xmlgen.h \
    xmlwriter.h

FORMS    += mainwindow.ui
