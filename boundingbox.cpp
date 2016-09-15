#include "boundingbox.h"

BoundingBox::BoundingBox() {}

void BoundingBox::setRadialAcceleration(float radialAcceleration) {
    Vec2 acc(radialAcceleration * std::cos(angle), radialAcceleration * std::sin(angle));
    acceleration = acc;
}

void BoundingBox::update() {
    angularVelocity += angularAcceleration;
    angularVelocity *= angularFriction;
    angle += angularVelocity;

    Vec2::add(&velocity, acceleration);
    Vec2::multiply(&velocity, friction);
    Vec2::add(&position, velocity);
}

bool BoundingBox::isOutOfScreenBounds(int screenWidth, int screenHeight) {
    return (this->position.x + this->width / 2.0) > screenWidth ||
           (this->position.x - this->width / 2.0) < -screenWidth ||
           (this->position.y + this->height / 2.0) > screenHeight ||
           (this->position.y - this->height / 2.0) < -screenHeight;
}
