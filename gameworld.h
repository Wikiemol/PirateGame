#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "ship.h"
#include "vec2.h"
#include "aiship.h"
#include "boundingbox.h"
#include "openglrenderer.h"
#include "texturedrectangleprogram.h"
#include "rectangleprogram.h"
#include <vector>

class GameWorld
{
public:
    GameWorld();
    void update();
    void addAIShip(AIShip ship);
    void setShip(Ship ship);
    void setShipRenderer(TexturedRectangleProgram &renderer);
    void setCanonBallRenderer(RectangleProgram &renderer);
    void setWind(float magnitude, float angle);
    void setShipRenderer(TexturedRectangleProgram *renderer);
    void setCanonBallRenderer(RectangleProgram *renderer);
private:
    typedef struct camera {
        Vec2 position;
        float zoom = 1;
    } Camera;

    Ship ship;
    std::vector<AIShip> aiships;
    std::vector<BoundingBox> islands;
    TexturedRectangleProgram *shipRenderer;
    RectangleProgram *canonBallRenderer;
};

#endif // GAMEWORLD_H
