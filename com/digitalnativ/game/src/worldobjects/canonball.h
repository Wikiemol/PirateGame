#ifndef CANONBALL_H
#define CANONBALL_H
#include "gameobject.h"


class CanonBall : public GameObject
{
public:
    CanonBall();
    void onCollision(const GameObject *object);
    void update(qint64 timeElapsed);
};

#endif // CANONBALL_H
