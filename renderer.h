#ifndef RENDERER_H
#define RENDERER_H
#include "ship.h"
#include "texturedrectangleprogram.h"
#include "rectangleprogram.h"
#include "camera.h"
class Renderer
{
public:
    Renderer();
    static void init();
    static void setCamera(Camera &camera);
    static void drawShip(Ship ship);
    static void drawRect(GameObject box);
    static void setColor(int r, int g, int b, int a);
    static void drawTexturedRect(GameObject box);
    static void setScreenDimensions(int screenHalfWidth, int screenHalfHeight);
    static void drawShip(Ship ship, bool drawFlag, bool drawHealth);
    static void drawMenuIcon(GameObject icon);
    static void drawCircle(GameObject circle);
private:
    static TexturedRectangleProgram texturedRectangleRenderer;
    static RectangleProgram circleRenderer;
    static RectangleProgram rectRenderer;
    static bool initialized;
    static Camera camera;
    static QColor color;
    static int screenHalfWidth;
    static int screenHalfHeight;
};

#endif // RENDERER_H
