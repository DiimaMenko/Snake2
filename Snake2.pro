#-------------------------------------------------
#
# Project created by QtCreator 2015-12-26T22:00:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Snake.cpp \
    Field.cpp

HEADERS  += mainwindow.h \
    Snake.h \
    Field.h

FORMS    += mainwindow.ui
