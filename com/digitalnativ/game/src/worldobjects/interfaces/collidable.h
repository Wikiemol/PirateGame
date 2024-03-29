#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include "worldobjects/gameobject.h"


class Collidable
{
public:
    virtual bool isCollided(GameObject* object) = 0;
};

#endif // COLLIDABLE_H
