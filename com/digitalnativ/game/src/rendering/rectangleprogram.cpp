#include "rectangleprogram.h"

RectangleProgram::RectangleProgram() { }

void RectangleProgram::init(const char* vertexShaderFile, const char* fragmentShaderFile) {
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    vertexShader.compileSourceFile(vertexShaderFile);

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    fragmentShader.compileSourceFile(fragmentShaderFile);

    addShader(&vertexShader);
    addShader(&fragmentShader);
    link();
    bind();

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    GLfloat bufferData[] = {
        //Position				//Texcoord
       -0.5f,  -0.5f, 0.0f,		1.0, 1.0,
        0.5f,  -0.5f, 0.0f,		0.0, 1.0,
        0.5f,   0.5f, 0.0f, 	0.0, 0.0,
       -0.5f,   0.5f, 0.0f,		1.0, 0.0
    };

    glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(GL_FLOAT), bufferData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    GLuint pos = attributeLocation("pos");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    release();
}

void RectangleProgram::draw(GameObject &rectangle, int screenWidth, int screenHeight) {
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBindVertexArray(vertexArrayObject);
    GLint screenDimensions = uniformLocation("screenDimensions");
    GLint objectDimensions = uniformLocation("objectDimensions");
    GLint translation = uniformLocation("translation");
    GLint rotation = uniformLocation("rotation");
    GLint color = uniformLocation("color");
    if (screenDimensions == -1 || objectDimensions == -1
            || translation == -1 || rotation == -1 || color == -1) {
        qWarning() << "Rectangle Program uniform not found.";
    }

    glUniform2f(screenDimensions, screenWidth, screenHeight);
    glUniform2f(objectDimensions, rectangle.width, rectangle.height);
    glUniform2f(translation, rectangle.position.x, rectangle.position.y);
    glUniform4f(color, this->color.red() / 255.0f, this->color.green() / 255.0f, this->color.blue() / 255.0f, this->color.alpha() / 255.0f);

    GLfloat rotationMatrix[4] = {};
    rotationMatrix[0] = std::cos(rectangle.angle);
    rotationMatrix[1] = -std::sin(rectangle.angle);
    rotationMatrix[2] = std::sin(rectangle.angle);
    rotationMatrix[3] = std::cos(rectangle.angle);
    glUniformMatrix2fv(rotation, 1, GL_FALSE, rotationMatrix);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    release();
}

QColor RectangleProgram::getColor() const
{
    return color;
}

void RectangleProgram::setColor(const QColor &value)
{
    color = value;
}
