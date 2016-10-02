#include <QDebug>
#include <QImage>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QRgb>
#include <QTimer>
#include <iostream>
#include <string.h>
#include "texturedrectangleprogram.h"
#include "openglwidget.h"
#include "renderer.h"
#include "defaults.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

OpenGLWidget::~OpenGLWidget()
{
    GameWorld::destroyInstance();
    world = NULL;
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    Renderer::init();
    glClearColor(0.5, 0.5, 0.5, 1);
    texturedRectangleProgram.init();
    GLuint noSailsTex;
    GLuint allSailsTex;
    GLuint mainSailsTex;
    GLuint foreAndAftSailsTex;
    TexturedRectangleProgram::getTexture(":/images/no_sails.png", &noSailsTex);
    TexturedRectangleProgram::getTexture(":/images/all_sails.png", &allSailsTex);
    TexturedRectangleProgram::getTexture(":/images/main_sails.png", &mainSailsTex);
    TexturedRectangleProgram::getTexture(":/images/foreandaft_sails.png", &foreAndAftSailsTex);

    Ship *playerShip = new Ship();
    playerShip->setTextures(allSailsTex, mainSailsTex, foreAndAftSailsTex, noSailsTex);
    playerShip->width = 300;
    playerShip->height = 120;
    playerShip->setIsControllable(true);

    AIShip *otherShip = new AIShip();
    otherShip->setTextures(allSailsTex, mainSailsTex, foreAndAftSailsTex, noSailsTex);
    otherShip->width = 300;
    otherShip->height = 120;
    otherShip->position.x = -500;
    otherShip->setTarget(Vec2(10, 10));

    otherShip->setState(AIShip::ATTACK);

    world = GameWorld::getInstance();
    world->addObject(otherShip);
    world->addObject(playerShip);
    world->init();
    world->setScreenDimensions(this->width(), this->height());
    world->setWind(1, M_PI);

    QObject::connect(&gameLoopTimer, SIGNAL(timeout()), this, SLOT(update()));
//    gameLoopTimer.setTimerType(Qt::PreciseTimer);
    gameLoopTimer.setInterval(16);
    gameLoopTimer.start();
    GLuint err = GL_NO_ERROR;
    while ((err = glGetError()) != GL_NO_ERROR) {
        qDebug() << "Error: " << (void *) err;
    }
}

void OpenGLWidget::resizeGL(int w, int h) {
    world->setScreenDimensions(this->width(), this->height());
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world->update();
    world->renderWorld(this->width(), this->height());
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    world->keyPressEvent(event);
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    world->keyReleaseEvent(event);
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    world->mousePressEvent(event);
}
