#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QKeyEvent>
#include "texturedrectangleprogram.h"
#include "gameobject.h"
#include "rectangleprogram.h"
#include "ship.h"
#include "aiship.h"
#include "gameworld.h"

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:

    OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();
    void initializeGL();
    void resizeGL(int w, int h);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
public slots:
    void paintGL();
private:
    GLuint texture;
    QOpenGLShaderProgram texturedRectProgram;
    TexturedRectangleProgram texturedRectangleProgram;
    RectangleProgram circleRenderer;
    QTimer gameLoopTimer;
    GameWorld *world = NULL;
};

#endif // OPENGLWIDGET_H
