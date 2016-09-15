#ifndef TEXTUREDRECTANGLEPROGRAM_H
#define TEXTUREDRECTANGLEPROGRAM_H
#include <QOpenGLShaderProgram>
#include "boundingbox.h"
#include "openglrenderer.h"


class TexturedRectangleProgram : public OpenGLRenderer
{
public:
    TexturedRectangleProgram();
    static void createTexture(const char *fileName, GLuint *texture);
    void draw(BoundingBox &rectangle, int screenWidth, int screenHeight);
    void init();
    void init(const char *vertexShader, const char *fragmentShader);
    void operator =(TexturedRectangleProgram &other);


private:
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;
};

#endif // TEXTUREDRECTANGLEPROGRAM_H
