#include "texturedrectangleprogram.h"
#include "boundingbox.h"
#include <QOpenGLShader>
#include <QImage>

TexturedRectangleProgram::TexturedRectangleProgram() {}

void TexturedRectangleProgram::init() {
    init(NULL, NULL);
}

void TexturedRectangleProgram::init(const char *vertexShaderFile, const char *fragmentShaderFile) {
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    if (vertexShaderFile == NULL) {
        vertexShader.compileSourceFile(":/vertex.vert");
    } else {
        vertexShader.compileSourceCode(vertexShaderFile);
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    if (fragmentShaderFile == NULL) {

        fragmentShader.compileSourceFile(":/fragment.frag");
    } else {
        vertexShader.compileSourceCode(fragmentShaderFile);
    }

    addShader(&vertexShader);
    addShader(&fragmentShader);
    link();
    bind();

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    GLfloat bufferData[] = {
        //Position				//Texcoord
       -1.0f,  -1.0f, 0.0f,		0.0, 0.0,
        1.0f,  -1.0f, 0.0f,		1.0, 0.0,
        1.0f,   1.0f, 0.0f, 	1.0, 1.0,
       -1.0f,   1.0f, 0.0f,		0.0, 1.0
    };

    glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(GL_FLOAT), bufferData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    GLuint pos = attributeLocation("pos");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
    GLuint texCoord = attributeLocation("texCoord");
    glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void *) (3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(texCoord);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    release();
}

void TexturedRectangleProgram::createTexture(const char* fileName, GLuint *texture) {

    QImage image;
    if (!image.load(fileName)) {
        qWarning() << "Image " << fileName << " failed to load.";
    }
    const int width = image.width();
    const int height = image.height();

    GLubyte pixels[width * height * 4];
    memset(pixels, 0, width * height * 4 * sizeof(GLubyte));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            QRgb rgb = image.pixel(x, y);
            GLubyte red = qRed(rgb);
            GLubyte green = qGreen(rgb);
            GLubyte blue = qBlue(rgb);
            GLubyte alpha = qAlpha(rgb);
            int pixelIndex = (x + y * width) * 4;
            pixels[pixelIndex] = red;
            pixels[pixelIndex + 1] = green;
            pixels[pixelIndex + 2] = blue;
            pixels[pixelIndex + 3] = alpha;
        }
    }

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TexturedRectangleProgram::draw(BoundingBox &rectangle, int screenWidth, int screenHeight) {
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBindVertexArray(vertexArrayObject);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, rectangle.texture);
    GLint screenDimensions = uniformLocation("screenDimensions");
    GLint objectDimensions = uniformLocation("objectDimensions");
    GLint translation = uniformLocation("translation");
    GLint rotation = uniformLocation("rotation");
    GLint tex = uniformLocation("tex");
    if (screenDimensions == -1 || objectDimensions == -1
            || translation == -1 || rotation == -1 || tex == -1) {
        qWarning() << "Textured Rectangle Program uniform not found.";
    }

    glUniform2f(screenDimensions, screenWidth, screenHeight);
    glUniform2f(objectDimensions, rectangle.width, rectangle.height);
    glUniform2f(translation, rectangle.position.x, rectangle.position.y);

    GLfloat rotationMatrix[4] = {};
    rotationMatrix[0] = std::cos(rectangle.angle);
    rotationMatrix[1] = -std::sin(rectangle.angle);
    rotationMatrix[2] = std::sin(rectangle.angle);
    rotationMatrix[3] = std::cos(rectangle.angle);
    glUniformMatrix2fv(rotation, 1, GL_FALSE, rotationMatrix);
    glUniform1i(tex, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    release();
}
