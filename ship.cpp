#include <cmath>
#include <QDateTime>
#include "ship.h"

Ship::Ship() {  }

void Ship::setWind(float magnitude, float angle) {
    wind.x = std::cos(angle) * magnitude;
    wind.y = std::sin(angle) * magnitude;
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

void Ship::update() {
    Vec2 direction(std::cos(angle), std::sin(angle));
    acceleration.x = 0;
    acceleration.y = 0;
    if (mainSails) {
        Vec2 windAcc;
        windAcc.x = direction.x;
        windAcc.y = direction.y;
        Vec2::multiply(&windAcc, Vec2::dot(windAcc, wind));
        Vec2::add(&acceleration, windAcc);
    }
    if (foreAndAftSails) {
        Vec2 liftAcc;
        liftAcc.x = direction.x;
        liftAcc.y = direction.y;
        Vec2 perpWind(wind.y, -wind.x);
        Vec2::multiply(&perpWind, 0.5);
        float dot = Vec2::dot(perpWind, liftAcc);
        if (dot < 0) {
            Vec2::multiply(&perpWind, -1);
            dot = Vec2::dot(perpWind, liftAcc);
        }

        Vec2::multiply(&liftAcc, dot);
        Vec2::add(&acceleration, liftAcc);
    }
    BoundingBox::update();

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

void Ship::fireCanons() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    if (lastCanonFire == -1 || (currentTime - lastCanonFire) > 2000) {
        float interval = (this->width / (float) numberOfCanons);
        for (int i = 0; i < numberOfCanons; i++) {
            Vec2 direction = getDirection();
            Vec2 position = direction;

            Vec2::multiply(&position, i * interval);
            BoundingBox box;
            box.position = position;
            box.position.x += this->position.x;
            box.position.y += this->position.y;
            box.velocity.x = direction.y * 10;
            box.velocity.y = -direction.x * 10;
            Vec2::multiply(&direction, -this->width / 2.0);
            Vec2::add(&box.position, direction);
            box.width = 7;
            box.height = 7;
            canons.push_back(box);
        }
        lastCanonFire = currentTime;

    }
}

int Ship::getNumberOfCanonBalls() {
    return canons.size();
}

void Ship::deleteCanon(int i) {
    canons.erase(canons.begin() + i);
}

BoundingBox* Ship::getCanonBallAt(int i) {
    return &canons.at(i);
}

Vec2 Ship::getDirection() {
    Vec2 direction(std::cos(angle), std::sin(angle));
    return direction;
}
