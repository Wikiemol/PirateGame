#include "canonball.h"
#include "gameworld.h"

CanonBall::CanonBall()
{
    addType(GType::CANONBALL);
    setIsDangerous(true);
    setDamage(5);
}

void CanonBall::update(qint64 timeElapsed) {
    if (isOutOfRange()) {
        GameWorld *world = GameWorld::getInstance();
        world->onDestroy(this);
    }
    GameObject::update(timeElapsed);
}

void CanonBall::onCollision(const GameObject *object)
{
    if (!object->isType(GType::CANONBALL)) {
        GameWorld *world = GameWorld::getInstance();
        world->onDestroy(this);
    }
}
