#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H
#include <QKeyEvent>
#include "worldobjects/gameobject.h"

class Controllable
{
public:
    virtual void keyPressEvent(QKeyEvent* event, const GameObject* selected) = 0;
    virtual void keyReleaseEvent(QKeyEvent* event) = 0;
};

#endif // CONTROLLABLE_H
