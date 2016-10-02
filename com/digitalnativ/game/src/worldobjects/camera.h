#ifndef CAMERA_H
#define CAMERA_H
#include "utils/vec2.h"


class Camera
{
public:
    Vec2 position;
    float zoom = 1;
    Camera();
};

#endif // CAMERA_H
