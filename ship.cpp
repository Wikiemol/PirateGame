#include <cmath>
#include <QDateTime>
#include "gameworld.h"
#include "ship.h"
#include "canonball.h"

Ship::Ship() {
    friction = SHIP_FRICTION;
    angularFriction = SHIP_ANGULAR_FRICTION;
    maxAngularVelocity = MAX_ANGULAR_VELOCITY;
    type = SHIP;
}

void Ship::setWind(float magnitude, float angle) {
    wind.x = std::cos(angle) * magnitude;
    wind.y = std::sin(angle) * magnitude;
}

void Ship::setWind(Vec2 value)
{
   wind = value;
}

void Ship::toggleMainSails() {
    mainSails = !mainSails;
}

void Ship::toggleForeAndAftSails() {
    foreAndAftSails = !foreAndAftSails;
}

void Ship::setTextures(uint allSails, uint mainSails,
                       uint foreAndAftSails, uint noSails) {
    this->all_sails_tex = allSails;
    this->main_sails_tex = mainSails;
    this->foreandaft_sails_tex = foreAndAftSails;
    this->no_sails_tex = noSails;
}

Vec2 Ship::getLiftAcc(Vec2 unitDirection) {
    Vec2 liftAcc;
    liftAcc.x = unitDirection.x;
    liftAcc.y = unitDirection.y;
    Vec2 perpWind(wind.y, -wind.x);
    Vec2::multiply(&perpWind, 0.7);
    float dot = Vec2::dot(perpWind, liftAcc);
    if (dot < 0) {
        Vec2::multiply(&perpWind, -1);
        dot = Vec2::dot(perpWind, liftAcc);
    }

    Vec2::multiply(&liftAcc, dot);
    return liftAcc;
}

qint64 Ship::getLastCanonFire() const
{
    return lastCanonFire;
}

void Ship::keyPressEvent(QKeyEvent *event, const GameObject* selected)
{
    switch(event->key()) {
        case Qt::Key_A:
            angularAcceleration = PLAYER_ANGULAR_ACC;
        break;
        case Qt::Key_D:
            angularAcceleration = -PLAYER_ANGULAR_ACC;
        break;
        case Qt::Key_S:
            toggleMainSails();
        break;
        case Qt::Key_W:
            toggleForeAndAftSails();
        break;
        case Qt::Key_Space:
            if (selected != NULL) {
                fireCanons(selected->position);
            } else {
                fireCanons();
            }
        break;
    }
}

void Ship::keyReleaseEvent(QKeyEvent *event)
{

    switch(event->key()) {
        case Qt::Key_A:
        case Qt::Key_D:
            angularAcceleration = 0;
        break;
        case Qt::Key_W:
        break;
    }
}


int Ship::getHealth() const
{
    return health;
}

void Ship::setHealth(int value)
{
    if (value >= 0) {
        health = value;
    } else {
        health = 0;
    }
}

int Ship::getMaxhealth() const
{
    return maxhealth;
}

void Ship::setMaxhealth(int value)
{
    maxhealth = value;
}

void Ship::update(qint64 timeElapsed) {

    Vec2 direction(std::cos(angle), std::sin(angle));
    acceleration.x = 0;
    acceleration.y = 0;
    if (mainSails) {
        Vec2 windAcc;
        windAcc.x = direction.x;
        windAcc.y = direction.y;
        Vec2::multiply(&windAcc, Vec2::dot(windAcc, wind));
//        Vec2::subtract(&windAcc, velocity);
//        windAcc = Vec2::multiply(direction, Vec2::dot(windAcc, windAcc) / 50);
        Vec2::add(&acceleration, windAcc);
    }
    if (foreAndAftSails) {
        Vec2 liftAcc = getLiftAcc(direction);
        Vec2::add(&acceleration, liftAcc);
    }
    GameObject::update(timeElapsed);

    if (!mainSails && !foreAndAftSails) {
        texture = no_sails_tex;
    } else if (mainSails && !foreAndAftSails) {
        texture = main_sails_tex;
    } else if (!mainSails && foreAndAftSails) {
        texture = foreandaft_sails_tex;
    } else if (mainSails && foreAndAftSails) {
        texture = all_sails_tex;
    }
}

void Ship::setFlag(const Flag &value)
{
    flag = value;
}

Ship::Flag Ship::getFlag() const
{
    return flag;
}

void Ship::fireCanons() {
    fireCanons(position);
}

void Ship::onCollision(const GameObject *object) {
    if (object->isDangerous()) {
        setHealth(getHealth() - object->getDamage());
    }
}

void Ship::fireCanons(Vec2 target) {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    if (lastCanonFire == -1 || (currentTime - lastCanonFire) > CANON_RELOAD_TIME) {
        float interval = (this->width / (float) numberOfCanons);
        for (int i = 0; i < numberOfCanons; i++) {
            Vec2 direction = getDirection();
            Vec2 position = direction;

            Vec2::multiply(&position, i * interval);
            CanonBall *canonBall = new CanonBall();
            canonBall->setParent(this);
            canonBall->position = position;
            canonBall->position.x += this->position.x;
            canonBall->position.y += this->position.y;
            canonBall->velocity.x = direction.y * CANON_VELOCITY;
            canonBall->velocity.y = -direction.x * CANON_VELOCITY;
            canonBall->setDestroyOnCollision(true);

            float targetDot;
            if (target.x == this->position.x && target.y == this->position.y) {
                targetDot = 1;
            } else {
                targetDot = Vec2::dot(canonBall->velocity, Vec2::subtract(target, this->position));
                targetDot /= std::abs(targetDot);
            }

            Vec2::multiply(&canonBall->velocity, targetDot);
            Vec2::multiply(&direction, -this->width / 2.0);
            Vec2::add(&canonBall->position, direction);
            canonBall->width = 50;
            canonBall->height = 50;
            canonBall->setInitialPosition(canonBall->position);
            canonBall->setRange(CANON_RANGE);
            GameWorld::getInstance()->addObject(canonBall);
//            canonBalls.push_back(canonBall);
        }
        lastCanonFire = currentTime;
    }
}

bool Ship::getMainSails() const
{
    return mainSails;
}

void Ship::setMainSails(bool value)
{
    mainSails = value;
}

bool Ship::getForeAndAftSails() const
{
    return foreAndAftSails;
}

void Ship::setForeAndAftSails(bool value)
{
    foreAndAftSails = value;
}

void Ship::operator=(const Ship &s)
{
    GameObject::operator =(s);
    all_sails_tex = s.all_sails_tex;
    no_sails_tex = s.no_sails_tex;
    main_sails_tex = s.main_sails_tex;
    foreandaft_sails_tex = s.foreandaft_sails_tex;
    mainSails = s.mainSails;
    foreAndAftSails = s.foreAndAftSails;
    numberOfCanons = s.numberOfCanons;
    canonBalls = s.canonBalls;
    lastCanonFire = s.lastCanonFire;
    flag = s.flag;
}

int Ship::getNumberOfCanonBalls() {
    return canonBalls.size();
}

GameObject* Ship::getCanonBallAt(int i) {
    return &canonBalls.at(i);
}

void Ship::removeCanonBallAt(int i) {
    canonBalls.erase(canonBalls.begin() + i);
}
