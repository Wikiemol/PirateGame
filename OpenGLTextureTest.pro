#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T12:32:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLTextureTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    vec2.cpp \
    texturedrectangleprogram.cpp \
    rectangleprogram.cpp \
    boundingbox.cpp \
    ship.cpp \
    aiship.cpp \
    gameworld.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    vec2.h \
    texturedrectangleprogram.h \
    rectangleprogram.h \
    boundingbox.h \
    ship.h \
    aiship.h \
    gameworld.h \
    openglrenderer.h

FORMS    += mainwindow.ui

DISTFILES += \
    vertex.vert \
    fragment.frag \
    circle.vert \
    circle.frag

RESOURCES += \
    resources.qrc
