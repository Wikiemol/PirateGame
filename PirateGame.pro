#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T12:32:44
#
#-------------------------------------------------

QT  += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_MAC_SDK = macosx10.12

TARGET = PirateGame
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -g

INCLUDEPATH += $$PWD/com/digitalnativ/game/src/
HEADERS += $$PWD/com/digitalnativ/game/src/*.h \
    com/digitalnativ/game/src/rendering/openglrenderer.h \
    com/digitalnativ/game/src/rendering/rectangleprogram.h \
    com/digitalnativ/game/src/rendering/renderer.h \
    com/digitalnativ/game/src/rendering/texturedrectangleprogram.h \
    com/digitalnativ/game/src/utils/vec2.h \
    com/digitalnativ/game/src/worldobjects/aiship.h \
    com/digitalnativ/game/src/worldobjects/camera.h \
    com/digitalnativ/game/src/worldobjects/canonball.h \
    com/digitalnativ/game/src/worldobjects/interfaces/collidable.h \
    com/digitalnativ/game/src/worldobjects/interfaces/controllable.h \
    com/digitalnativ/game/src/worldobjects/gamebutton.h \
    com/digitalnativ/game/src/worldobjects/gameobject.h \
    com/digitalnativ/game/src/worldobjects/gameobjectproperty.h \
    com/digitalnativ/game/src/worldobjects/ship.h

SOURCES += $$PWD/com/digitalnativ/game/src/*.cpp \
    com/digitalnativ/game/src/rendering/rectangleprogram.cpp \
    com/digitalnativ/game/src/rendering/renderer.cpp \
    com/digitalnativ/game/src/rendering/texturedrectangleprogram.cpp \
    com/digitalnativ/game/src/utils/vec2.cpp \
    com/digitalnativ/game/src/worldobjects/aiship.cpp \
    com/digitalnativ/game/src/worldobjects/camera.cpp \
    com/digitalnativ/game/src/worldobjects/canonball.cpp \
    com/digitalnativ/game/src/worldobjects/gamebutton.cpp \
    com/digitalnativ/game/src/worldobjects/gameobject.cpp \
    com/digitalnativ/game/src/worldobjects/gameobjectproperty.cpp \
    com/digitalnativ/game/src/worldobjects/ship.cpp

FORMS  += $$PWD/com/digitalnativ/game/mainwindow.ui

DISTFILES += $$PWD/com/digitalnativ/game/shaders/*.vert \
    README.md
DISTFILES += $$PWD/com/digitalnativ/game/shaders/*.frag

RESOURCES += \
    $$PWD/com/digitalnativ/game/resources.qrc
