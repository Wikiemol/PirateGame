#include "renderer.h"

Renderer::Renderer() {}

TexturedRectangleProgram Renderer::texturedRectangleRenderer;
RectangleProgram Renderer::circleRenderer;
RectangleProgram Renderer::rectRenderer;
bool Renderer::initialized = false;
Camera Renderer::camera;
QColor Renderer::color(255, 255, 255, 255);
int Renderer::screenHalfWidth;
int Renderer::screenHalfHeight;

void Renderer::init()
{
    texturedRectangleRenderer.init();
    circleRenderer.init(":/shaders/circle.vert", ":/shaders/circle.frag");
    rectRenderer.init(":/shaders/vertex.vert", ":/shaders/rectangle.frag");
    TexturedRectangleProgram::getTexture(":/images/flags/english_flag.png", NULL);
    TexturedRectangleProgram::getTexture(":/images/flags/spanish_flag.png", NULL);
    TexturedRectangleProgram::getTexture(":/images/flags/roger_flag.png", NULL);
    TexturedRectangleProgram::getTexture(":/images/flags/french_flag.png", NULL);
    initialized = true;
}

void Renderer::setScreenDimensions(int screenHalfWidth, int screenHalfHeight) {
    Renderer::screenHalfWidth = screenHalfWidth;
    Renderer::screenHalfHeight = screenHalfHeight;
}

void Renderer::setCamera(Camera &camera)
{
    Renderer::camera = camera;

}

void Renderer::setColor(int r, int g, int b, int a) {
    color.setRgb(r, g, b, a);
}

void Renderer::drawMenuIcon(GameObject icon) {
    texturedRectangleRenderer.draw(icon, screenHalfWidth, screenHalfHeight);
}

void Renderer::drawTexturedRect(GameObject box) {
    Vec2::subtract(&box.position, camera.position);
    box.width *= camera.zoom;
    box.height *= camera.zoom;
    Vec2::multiply(&box.position, camera.zoom);
    texturedRectangleRenderer.draw(box, screenHalfWidth, screenHalfHeight);
}

void Renderer::drawRect(GameObject box)
{
    Vec2::subtract(&box.position, camera.position);
    box.width *= camera.zoom;
    box.height *= camera.zoom;
    Vec2::multiply(&box.position, camera.zoom);
    rectRenderer.setColor(color);
    rectRenderer.draw(box, screenHalfWidth, screenHalfHeight);
}

void Renderer::drawCircle(Vec2 position, float radius) {
    GameObject circle;
    circle.position = position;
    circle.width = radius * 2;
    circle.height = radius * 2;
    drawCircle(circle);
}

void Renderer::drawCircle(GameObject circle) {
        Vec2::subtract(&circle.position, camera.position);
        circle.width *= camera.zoom;
        circle.height *= camera.zoom;
        Vec2::multiply(&circle.position, camera.zoom);
        circleRenderer.setColor(color);
        circleRenderer.draw(circle, screenHalfWidth, screenHalfHeight);
}

void Renderer::drawShip(Ship ship)
{
    Vec2::subtract(&ship.position, camera.position);
    ship.width *= camera.zoom;
    ship.height *= camera.zoom;
    Vec2::multiply(&ship.position, camera.zoom);
    texturedRectangleRenderer.draw(ship, screenHalfWidth, screenHalfHeight);
}

void Renderer::drawShip(Ship ship, bool drawHealth)
{
    drawShip(ship);
    Ship::Flag flag = ship.getFlag();
    if (flag != Ship::NONE) {
        GameObject flagIcon;
        if (flag == Ship::JOLLY_ROGER) {
            TexturedRectangleProgram::getTexture(":/images/flags/roger_flag.png", &flagIcon.texture);
        } else if (flag == Ship::ENGLISH) {
            TexturedRectangleProgram::getTexture(":/images/flags/english_flag.png", &flagIcon.texture);
        } else if (flag == Ship::SPANISH) {
            TexturedRectangleProgram::getTexture(":/images/flags/spanish_flag.png", &flagIcon.texture);
        } else if (flag == Ship::FRENCH) {
            TexturedRectangleProgram::getTexture(":/images/flags/french_flag.png", &flagIcon.texture);
        }
        flagIcon.position = ship.position;
        Renderer::drawTexturedRect(flagIcon);
    }

    if (drawHealth) {

        Renderer::setColor(255, 0, 0, 255);
        GameObject health;
        health.width = ship.getHealth();
        health.height = 10;
        health.position = ship.position;
        health.position.y += ship.height * 1.1;
        Renderer::drawRect(health);
    }
}

void Renderer::getTexture(const char* fileName, GLuint* texture) {
    TexturedRectangleProgram::getTexture(fileName, texture);
}
