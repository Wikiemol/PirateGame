#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H
#include "boundingbox.h"
#include <QOpenGLShaderProgram>

class OpenGLRenderer : public QOpenGLShaderProgram
{
public:
    virtual void init(const char* vertexShader, const char* fragmentShader) = 0;
    virtual void draw(BoundingBox &drawable, int screenWidth, int screenHeight) = 0;
};

#endif // OPENGLRENDERER_H
