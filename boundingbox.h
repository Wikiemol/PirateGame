#ifndef TEXTUREDRECTANGLE_H
#define TEXTUREDRECTANGLE_H
#include "vec2.h"


class BoundingBox
{
public:
    int width = 100;
    int height = 100;

    Vec2 acceleration;
    Vec2 velocity;
    Vec2 position;
    float friction = 1;

    float angularAcceleration = 0;
    float angularVelocity = 0;
    float angle = 0;

    float angularFriction = 1;

    uint texture = 0;

    BoundingBox();
    void setRadialAcceleration(float radialAcceleration);
    void update();
    bool isOutOfScreenBounds(int width, int height);
};

#endif // TEXTUREDRECTANGLE_H
