#ifndef RECTANGLEPROGRAM_H
#define RECTANGLEPROGRAM_H
#include "gameobject.h"
#include "openglrenderer.h"
#include <QOpenGLShaderProgram>
#include <QColor>

class RectangleProgram : public OpenGLRenderer
{
public:
    RectangleProgram();
    void init(const char *vertexShaderFile, const char *fragmentShaderFile);
    void draw(GameObject &rectangle, int screenWidth, int screenHeight);

    QColor getColor() const;
    void setColor(const QColor &value);

private:
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;
    QColor color;
};

#endif // RECTANGLEPROGRAM_H
