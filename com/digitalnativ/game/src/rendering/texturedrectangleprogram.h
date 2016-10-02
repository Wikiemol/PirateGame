#ifndef TEXTUREDRECTANGLEPROGRAM_H
#define TEXTUREDRECTANGLEPROGRAM_H
#include <QOpenGLShaderProgram>
#include <unordered_map>
#include "worldobjects/gameobject.h"
#include "openglrenderer.h"


class TexturedRectangleProgram : public OpenGLRenderer
{
public:
    TexturedRectangleProgram();
    static bool textureExists(const char *fileName);
    static void getTexture(const char *fileName, GLuint *texture);
    void draw(GameObject &rectangle, int screenWidth, int screenHeight);
    void init();
    void init(const char *vertexShader, const char *fragmentShader);
    void operator =(TexturedRectangleProgram &other);
private:
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;
    static std::unordered_map<const char*, GLuint> fileNameToTexturesMap;
};

#endif // TEXTUREDRECTANGLEPROGRAM_H
