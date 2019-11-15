#-------------------------------------------------
#
# Project created by QtCreator 2019-11-12T10:00:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhotoViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filemanagement.cpp \
    settingsmanagement.cpp

HEADERS  += mainwindow.h \
    filemanagement.h \
    constans.h \
    settingsmanagement.h

FORMS    += mainwindow.ui
