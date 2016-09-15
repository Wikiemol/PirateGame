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

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0, 0, 0, 1);
    texturedRectangleProgram.init();
    GLuint noSailsTex;
    GLuint allSailsTex;
    GLuint mainSailsTex;
    GLuint foreAndAftSailsTex;
    texturedRectangleProgram.createTexture(":/images/no_sails.png", &noSailsTex);
    texturedRectangleProgram.createTexture(":/images/all_sails.png", &allSailsTex);
    texturedRectangleProgram.createTexture(":/images/main_sails.png", &mainSailsTex);
    texturedRectangleProgram.createTexture(":/images/foreandaft_sails.png", &foreAndAftSailsTex);
    ship.setTextures(allSailsTex, mainSailsTex, foreAndAftSailsTex, noSailsTex);
    otherShip.setTextures(allSailsTex, mainSailsTex, foreAndAftSailsTex, noSailsTex);
    circleRenderer.init(":/circle.vert", ":/circle.frag");

    ship.friction = 0.9;
    ship.setWind(1, M_PI);
    ship.width = 150;
    ship.height = 60;

    otherShip.setWind(1, M_PI);
    otherShip.friction = 0.9;
    otherShip.width = 150;
    otherShip.height = 60;

    world.setCanonBallRenderer(&circleRenderer);
    world.setShipRenderer(&texturedRectangleProgram);

    world.addAIShip(otherShip);
    world.setShip(ship);


    QObject::connect(&gameLoopTimer, SIGNAL(timeout()), this, SLOT(update()));
    gameLoopTimer.setInterval(33);
    gameLoopTimer.start();
    GLuint err = GL_NO_ERROR;
    while ((err = glGetError()) != GL_NO_ERROR) {
        qDebug() << "Error: " << (void *) err;
    }

}

void OpenGLWidget::resizeGL(int w, int h) {
}

bool yes = false;
void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.update();
    ship.angularFriction = 0.9;
    ship.update();
    texturedRectangleProgram.draw(ship, this->width(), this->height());
    otherShip.update();
    texturedRectangleProgram.draw(otherShip, this->width(), this->height());
    for (int i = 0; i < ship.getNumberOfCanonBalls(); i++) {
        BoundingBox *canonball = ship.getCanonBallAt(i);
        if (canonball->isOutOfScreenBounds(width(), height())) {
            ship.deleteCanon(i);
            i--;
            continue;
        }
        canonball->update();
        circleRenderer.draw(*canonball, width(), height());
    }

    GLuint err = GL_NO_ERROR;
    while ((err = glGetError()) != GL_NO_ERROR) {
        qDebug() << "Error: " << (void *) err;
    }
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_A:
            ship.angularAcceleration = 0.01;
        break;
        case Qt::Key_D:
            ship.angularAcceleration = -0.01;
        break;
        case Qt::Key_S:
            ship.toggleMainSails();
        break;
        case Qt::Key_W:
            ship.toggleForeAndAftSails();
        break;
        case Qt::Key_Space:
            ship.fireCanons();
        break;
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_A:
        case Qt::Key_D:
            ship.angularAcceleration = 0;
        break;
        case Qt::Key_W:
        break;
    }
}
