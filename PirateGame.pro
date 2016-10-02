#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T12:32:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_MAC_SDK = macosx10.12

TARGET = PirateGame
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -g



SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    vec2.cpp \
    texturedrectangleprogram.cpp \
    rectangleprogram.cpp \
    ship.cpp \
    aiship.cpp \
    gameworld.cpp \
    gamebutton.cpp \
    renderer.cpp \
    camera.cpp \
    gameobject.cpp \
    gameobjectproperty.cpp \
    addable.cpp \
    canonball.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    vec2.h \
    texturedrectangleprogram.h \
    rectangleprogram.h \
    gameobject.h \
    ship.h \
    aiship.h \
    gameworld.h \
    openglrenderer.h \
    collidable.h \
    gamebutton.h \
    renderer.h \
    camera.h \
    gameobject.h \
    defaults.h \
    gameobjectproperty.h \
    controllable.h \
    canonball.h

FORMS    += mainwindow.ui

DISTFILES += \
    vertex.vert \
    fragment.frag \
    circle.vert \
    circle.frag \
    rectangle.frag

RESOURCES += \
    resources.qrc
