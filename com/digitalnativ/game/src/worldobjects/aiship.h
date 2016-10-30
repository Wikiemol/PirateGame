#ifndef AISHIP_H
#define AISHIP_H
#include "ship.h"
#include <deque>
#include <unordered_map>


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
    void see(const GameObject *object);
private:
    typedef long ObjId;
    typedef qint64 LastSeen;
    std::deque<Vec2> lastTargetPositions;
    std::unordered_map<ObjId, LastSeen> seen;

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
