#include "gameobject.h"

long GameObject::_idCounter = 0;
GameObject::GameObject() {
    type = GAMEOBJECT;
    _id = GameObject::createId();
}

GameObject::~GameObject()
{

}


void GameObject::setRadialAcceleration(float radialAcceleration) {
    Vec2 acc(radialAcceleration * std::cos(angle), radialAcceleration * std::sin(angle));
    acceleration = acc;
}

void GameObject::update(qint64 timeElapsed) {
//    float times = (double) timeElapsed / 33.0;
    float times = 16 / 33.0;
    angularVelocity += angularAcceleration;
    angularVelocity *= angularFriction;
    if (angularVelocity > maxAngularVelocity) {
        angularVelocity = maxAngularVelocity;
    } else if (angularVelocity < -maxAngularVelocity) {
        angularVelocity = -maxAngularVelocity;
    }

    angle += angularVelocity * times;

    Vec2::add(&velocity, acceleration);
    Vec2::multiply(&velocity, friction);

    Vec2::add(&position, Vec2::multiply(velocity, times));
}

GameObject::Type GameObject::getType() const
{
    return type;
}

void GameObject::setType(const Type &value)
{
    type = value;
}

void GameObject::setRange(float value)
{
    range = value;
}

void GameObject::setInitialPosition(const Vec2 &value)
{
    initialPosition = value;
}

bool GameObject::isOutOfRange() {
    if (range != 0) {
        Vec2 directionToInit = Vec2::subtract(position, initialPosition);
        float distanceToInit = Vec2::dot(directionToInit, directionToInit);
        return distanceToInit > range * range;
    }
    return false;
}

Vec2 GameObject::getInitialPosition() const
{
    return initialPosition;
}

float GameObject::getRange() const
{
    return range;
}

bool GameObject::isControllable() const
{
    return _isControllable;
}

void GameObject::setIsControllable(bool value)
{
    _isControllable = value;
}

bool GameObject::destroyOnCollision() const
{
    return _destroyOnCollision;
}

void GameObject::setDestroyOnCollision(bool value)
{
    _destroyOnCollision = value;
}

GameObject *GameObject::getParent() const
{
    return parent;
}

void GameObject::setParent(GameObject *value)
{
    parent = value;
}

bool GameObject::isDangerous() const
{
    return _isDangerous;
}

int GameObject::getDamage() const
{
    return damage;
}

void GameObject::setDamage(int value)
{
    damage = value;
}

void GameObject::see(const GameObject *object) {
    object;
}

float GameObject::getSight() const
{
    return _sight;
}

void GameObject::setSight(float sight)
{
    _sight = sight;
}

long GameObject::getId() const
{
    return _id;
}

void GameObject::setIsDangerous(bool isDangerous)
{
    _isDangerous = isDangerous;
}

bool GameObject::collidesWith(const GameObject &object) const
{
    return GameObject::colliding(*this, object);
}

//Override me
void GameObject::onCollision(const GameObject *object) {  }

Vec2 GameObject::getDirection() const {
    Vec2 direction(std::cos(angle), std::sin(angle));
    return direction;
}

std::vector<Vec2> GameObject::getAxes() const {
    std::vector<Vec2> result;
    Vec2 direction = getDirection();
    result.push_back(direction);
    result.push_back(Vec2(direction.y, -direction.x));
    return result;
}

std::vector<Vec2> GameObject::getVertices() const {
    std::vector<Vec2> axes = getAxes();
    Vec2 widthAxis = Vec2::multiply(axes.at(0), width);
    Vec2 heightAxis = Vec2::multiply(axes.at(1), height);
    Vec2 bottomLeft = Vec2::add(Vec2::add(position, Vec2::multiply(axes.at(0), -width / 2.0f)),
                                Vec2::multiply(axes.at(1), -height / 2.0f));
    Vec2 bottomRight = Vec2::add(bottomLeft, widthAxis);
    Vec2 topLeft = Vec2::add(bottomLeft, heightAxis);
    Vec2 topRight = Vec2::add(topLeft, widthAxis);

    std::vector<Vec2> vertices;
    vertices.push_back(bottomLeft);
    vertices.push_back(bottomRight);
    vertices.push_back(topLeft);
    vertices.push_back(topRight);
    return vertices;
}

long GameObject::createId()
{
    return ++_idCounter;
}

void GameObject::operator=(const GameObject &box)
{
    this->width = box.width;
    this->height = box.height;

    this->acceleration = box.acceleration;
    this->velocity = box.velocity;
    this->position = box.position;
    this->friction = box.friction;

    this->angularAcceleration = box.angularAcceleration;
    this->angularVelocity = box.angularVelocity;
    this->angle = box.angle;

    this->angularFriction = box.angularFriction;

    this->texture = box.texture;
    this->type = box.getType();
    this->initialPosition = box.getInitialPosition();
    this->range = box.getRange();
}

bool GameObject::colliding(const GameObject &a, const GameObject &b) {
    std::vector<Vec2> bAxes = b.getAxes();
    std::vector<Vec2> aVertices = a.getVertices();
    std::vector<Vec2> bVertices = b.getVertices();

    std::vector<Vec2> axes = a.getAxes();

    for (unsigned i = 0; i < bAxes.size(); i++) {
        axes.push_back(bAxes.at(i));
    }

    bool colliding = true;
    for (unsigned i = 0; i < axes.size(); i++) {
        Vec2 axis = axes.at(i);
        float aMax;
        float aMin;
        for (unsigned j = 0; j < aVertices.size(); j++) {
            Vec2 vertex = aVertices.at(j);
            float dot = Vec2::dot(vertex, axis);
            if (j == 0 || dot > aMax) {
                aMax = dot;
            }

            if (j == 0 || dot < aMin) {
                aMin = dot;
            }
        }

        float bMax;
        float bMin;
        for (unsigned j = 0; j < bVertices.size(); j++) {
            Vec2 vertex = bVertices.at(j);
            float dot = Vec2::dot(vertex, axis);
            if (j == 0 || dot > bMax) {
                bMax = dot;
            }

            if (j == 0 || dot < bMin) {
                bMin = dot;
            }
        }

        if (!(aMin <= bMax && bMin <= aMax)) {
            colliding = false;
            break;
       }
    }
    return colliding;
}

bool GameObject::pointInBox(Vec2 &point, GameObject &box) {
    std::vector<Vec2> axes = box.getAxes();
    std::vector<Vec2> vertices = box.getVertices();
    float xMin = Vec2::dot(axes.at(1), vertices.at(0));
    float xMax = Vec2::dot(axes.at(1), vertices.at(2));
    float yMin = Vec2::dot(axes.at(0), vertices.at(0));
    float yMax = Vec2::dot(axes.at(0), vertices.at(1));

    float pointX = Vec2::dot(axes.at(1), point);
    float pointY = Vec2::dot(axes.at(0), point);

    return (xMin <= pointX && pointX <= xMax && yMin <= pointY && pointY <= yMax);
}
