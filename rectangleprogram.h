#ifndef RECTANGLEPROGRAM_H
#define RECTANGLEPROGRAM_H
#include "boundingbox.h"
#include "openglrenderer.h"
#include <QOpenGLShaderProgram>


class RectangleProgram : public OpenGLRenderer
{
public:
    RectangleProgram();
    void init(const char *vertexShaderFile, const char *fragmentShaderFile);
    void draw(BoundingBox &rectangle, int screenWidth, int screenHeight);

private:
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;
};

#endif // RECTANGLEPROGRAM_H
