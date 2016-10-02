#include "canonball.h"
#include "gameworld.h"

CanonBall::CanonBall()
{
    type = GameObject::CANONBALL;
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
    if (object->getType() != GameObject::CANONBALL) {
        GameWorld *world = GameWorld::getInstance();
        world->onDestroy(this);
    }
}
