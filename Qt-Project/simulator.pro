#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T19:37:20
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    tile.cpp \
    tools.cpp \
    city.cpp \
    camera.cpp \
    simulation.cpp \
    camerascontainer.cpp \
    path.cpp \
    object.cpp \
    dialog.cpp \
    jsonparser.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    tile.h \
    tools.h \
    city.h \
    camera.h \
    simulation.h \
    camerascontainer.h \
    path.h \
    object.h \
    jsonparser.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

CONFIG += c++11
