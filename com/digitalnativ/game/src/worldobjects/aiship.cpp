#include <QDateTime>
#include "aiship.h"

AIShip::AIShip() {
//    Ship();
    addType(GType::AISHIP);
}

float AIShip::getTargetMovementRange() {
    if (lastTargetPositions.size() == 0) {
        return 0;
    }
    float maxX = lastTargetPositions.at(0).x;
    float maxY = lastTargetPositions.at(0).y;
    float minX = lastTargetPositions.at(0).x;
    float minY = lastTargetPositions.at(0).y;
    for (unsigned i = 1; i < lastTargetPositions.size(); i++) {
        Vec2 position = lastTargetPositions.at(i);
        if (position.x > maxX) {
            maxX = position.x;
        }

        if (position.x < minX) {
            minX = position.x;
        }

        if (position.y > maxY) {
            maxY = position.y;
        }

        if (position.y < minY) {
            minY = position.y;
        }
    }
    return (maxX - minX) * (maxY - minY);
}

void AIShip::update(qint64 timeElapsed) {
    AIShip::State state = getState();
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    if (lastTargetSnapShotTaken == -1 || currentTime - lastTargetSnapShotTaken > 50) {
        if (lastTargetPositions.size() >= 50) {
            lastTargetPositions.pop_front();
        }
        if (lastTargetPositions.size() < 50) {
            lastTargetPositions.push_back(target.position);
        }
        lastTargetSnapShotTaken = currentTime;
    }

    switch(state) {
        case WANDER:
        {
            Vec2 targetDirection = Vec2::subtract(target.position, position);
            float distToTargetSquared = Vec2::dot(targetDirection, targetDirection);
            if (distToTargetSquared >  30 * 30) {
                moveTowardTarget(target.position);
            } else {
                setForeAndAftSails(false);
                setMainSails(false);
                angularAcceleration = 0;
                angularVelocity = 0;
                chooseNewTarget();
            }
            break;
        }
        //Basic strategy is to get in front of or behind the other ship, broadside to stern, and fire
        //whenever we happen to be aimed at the player (or right in front of the player)
        //and our canons are loaded
        //Also, if we haven't been aimed at the player (i.e., we haven't fired) in a certain
        //amount of time, then we aim and fire at in front of the bow
        case ATTACK:
        {
            Vec2 targetShipDirection = target.getDirection();
            Vec2 stern = Vec2::multiply(targetShipDirection, -target.height * 4);
            Vec2::add(&stern, target.position);
            Vec2 bow = Vec2::multiply(targetShipDirection, target.height * 2);
            Vec2::add(&bow, target.position);
//            Vec2 directionToStern = Vec2::subtract(stern, position);
            Vec2 directionToBow = Vec2::subtract(bow, position);
            Vec2 directionToPosition = Vec2::subtract(target.position, position);

            Vec2 targetPoint;
            float dot = Vec2::dot(target.velocity, target.velocity);
            if (dot < 40 * 40) {
                targetPoint = target.position;
            } else {
                targetPoint = bow;
            }
            if (Vec2::dot(directionToPosition, directionToPosition) > CANON_RANGE * CANON_RANGE * 2.5) {
                moveTowardTarget(target.position);
            } else {
                if (getTargetMovementRange() < 10000) {
                    aimAndFire(target.position);
                } else if (currentTime - getLastCanonFire() > AI_MAX_NOFIRE_TIME) {
                    aimAndFire(bow);
                    if (CANON_RANGE > 500) {
                        setMainSails(true);
                    }
                } else {

                    Vec2 targetDirection = Vec2::subtract(targetPoint, position);
                    float distToTargetSquared = Vec2::dot(targetDirection, targetDirection);
                    if (distToTargetSquared > 30 * 30) {
                        if (targetPoint.x == target.position.x && targetPoint.y == target.position.y) {
                            moveTowardTarget(stern);
                        } else {
                            moveTowardTarget(bow);
                        }
                    } else {
                        aimAndFire(target.position);
                    }
                }

                if (currentTime - getLastCanonFire() < CANON_RELOAD_TIME + 1000) {
                    Vec2 direction = getDirection();
                    Vec2 directionToShip = Vec2::subtract(target.position, position);
                    if (std::abs(Vec2::dot(direction, Vec2::norm(directionToShip))) < 0.02 ||
                        std::abs(Vec2::dot(direction, Vec2::norm(directionToBow))) < 0.01) {
                        fireCanons(targetPoint);
                    }
                }
            }
            break;
        }
        case AIM_FIRE:
        {
            aimAndFire(target.position);
            break;
        }
        default: {
            break;
        }
    }
    Ship::update(timeElapsed);
}

void AIShip::aimAndFire(Vec2 target) {
    setForeAndAftSails(false);
    setMainSails(false);
    angularAcceleration = 0;
    Vec2 directionToTarget = Vec2::norm(Vec2::subtract(target, position));
    float dot = Vec2::dot(Vec2(0, 1), directionToTarget);
    //Doing it this way to avoid divide by 0
    int sign = 1;
    if (dot < 0) {
        sign = -1;
    }
    float angleToTarget = sign * std::acos(Vec2::dot(Vec2(1, 0), directionToTarget));
    float targetAttackAngle = normAngle(angleToTarget + M_PI / 2.0);

    if (std::abs(targetAttackAngle - normAngle(this->angle)) > 0.05)  {
        rotate(targetAttackAngle);
    } else {
        fireCanons(target);
    }
}

void AIShip::chooseNewTarget() {
    target.position = Vec2(std::rand() % WORLD_WIDTH - WORLD_WIDTH / 2.0, std::rand() % WORLD_HEIGHT - WORLD_HEIGHT / 2.0);
    target.angle = 2 * M_PI * (std::rand() / (float) RAND_MAX);
}

GameObject AIShip::getTarget() const
{
    return target;
}

void AIShip::setTarget(const GameObject &box) {
    target = box;
}

void AIShip::setTarget(const Vec2 &value)
{
    target.position = value;
}

/**
 * @brief AIShip::normAngle
 * Forces angle between [0, 2 * M_PI)
 * @param angle
 * @return
 */
float AIShip::normAngle(float angle) {
    float newAngle = std::fmod(angle,  2 *M_PI);
    if (newAngle < 0) {
        newAngle += 2 * M_PI;
    }
    return newAngle;
}

void AIShip::operator =(const AIShip& s) {
    Ship::operator =(s);
    state = s.state;
    target = s.target;
}

/**
 * @brief AIShip::predictLiftIneffectiveness
 * Hard to think of a good name for this function
 * Basically predicts how close the ship will be to its
 * target after an update given the angle of the ship
 * and assuming that only the foreandaft sails are unfurled
 *
 * We can minimize this function to find the best target angle
 * when going against the wind. Returns the square of the distance
 * after the predicted update
 * @param angle
 */
double AIShip::predictLiftIneffectiveness(float angle, Vec2 &target) {
    Ship phantomShip = *this;
    phantomShip.angle = angle;
    phantomShip.setForeAndAftSails(true);
    phantomShip.setMainSails(false);
    phantomShip.setWind(wind);
    phantomShip.update(33);
    Vec2 targetVector = Vec2::subtract(target, phantomShip.position);
    return Vec2::dot(targetVector, targetVector);
}

void AIShip::moveTowardTarget(Vec2 target) {
    Vec2 direction = getDirection();
    Vec2 targetDirection = Vec2::subtract(target, position);

    Vec2 unitTarget = Vec2::norm(targetDirection);

    Vec2 normWind = Vec2::norm(wind);
    float windDot = Vec2::dot(unitTarget, normWind);

    float dotProduct = Vec2::dot(unitTarget, Vec2(1, 0));
    float upDown = Vec2::dot(unitTarget, Vec2(0, 1));
    float targetAngle = normAngle((upDown > 0 ? 1 : -1) * std::acos(dotProduct));
    float otherAngle = targetAngle;

    double bestLiftIneffectiveness = predictLiftIneffectiveness(otherAngle, target);
    int iterations = 5;
    //Don't need anything fancy here, just
    //brute force find the angle that will get
    //the ship closest to the target. We tried gradient descent before //(probably just to look smart).
    //That took too many iterations to be accurate and also resulted
    //in a large floating point error when too far from the
    //world's origin
    for (int i = 0; i < iterations; i++) {
        float angle = -M_PI + i * (2 * M_PI) / (float) iterations;
        double liftIneffectiveness = predictLiftIneffectiveness(angle, target);
        if (liftIneffectiveness < bestLiftIneffectiveness) {
            bestLiftIneffectiveness = liftIneffectiveness;
            otherAngle = angle;
        }
    }

    if (windDot < 0 ) {
        setForeAndAftSails(true);
        targetAngle = otherAngle;
    }

    if (windDot + 1 == 0) {
        targetAngle += M_PI;
    }

    rotate(targetAngle);
    if (windDot > 0) {
        setMainSails(true);
    } else {
        setMainSails(false);
    }

    if (std::abs(Vec2::dot(direction, unitTarget) - 1) < 0.01) {
        moveForward();
    }
}

void AIShip::rotate(float targetAngle) {

    float currentAngle = normAngle(angle);

    if (std::abs(currentAngle - targetAngle) > std::abs(currentAngle - (targetAngle + 2 * M_PI))) {
        targetAngle += 2 * M_PI;
    } else  if (std::abs(currentAngle - targetAngle) > std::abs(currentAngle - (targetAngle - 2 * M_PI))) {
        targetAngle -= 2 * M_PI;
    }

    angularFriction = 0.9;
    if (std::abs(currentAngle - targetAngle) > 0.001) {
        float tempAngularVelocity = angularVelocity;
        float predictedAngle = currentAngle;
        while (angularFriction != 1 && std::abs(tempAngularVelocity) > 0.000001) {
            tempAngularVelocity *= angularFriction;
            predictedAngle += tempAngularVelocity;
            predictedAngle = normAngle(predictedAngle);
        }
        if (std::abs(predictedAngle - targetAngle) > 0.0001) {
            angularAcceleration = (targetAngle - currentAngle) / 150;
        } else {
            angularAcceleration = 0;
        }
    }
}

void AIShip::moveForward() {
    float windDot = Vec2::dot(getDirection(), wind);
    if (windDot > 0) {
        setMainSails(true);
        setForeAndAftSails(true);
    } else {
        setMainSails(false);
        setForeAndAftSails(true);
    }
}

AIShip::State AIShip::getState() const
{
    return state;
}

void AIShip::setState(const State &value)
{
    state = value;
}
