#ifndef AISHIP_H
#define AISHIP_H
#include "ship.h"
#include <deque>


class AIShip : public Ship
{
public:
    enum State {STOP, WANDER, ATTACK, FLEE, GO_STRAIGHT, MOVE_TOWARD_TARGET, AIM_FIRE};
    AIShip();
    State getState() const;
    void setState(const State &value);

    GameObject getTarget() const;
    void setTarget(const Vec2 &value);
    void setTarget(const GameObject &box);
    void operator =(const AIShip &s);

    void update(qint64 timeElapsed);
private:
    std::deque<Vec2> lastTargetPositions;
    qint64 lastTargetSnapShotTaken = -1;
    GameObject target;
    State state = WANDER;
    void rotate(float targetAngle);
    float getTargetMovementRange();
    void aimAndFire(Vec2 target);
    double predictLiftIneffectiveness(float angle, Vec2 &target);
    void chooseNewTarget();
    static float normAngle(float angle);
    void moveTowardTarget(Vec2 target);
    void moveForward();
};

#endif // AISHIP_H
