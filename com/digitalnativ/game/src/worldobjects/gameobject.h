#ifndef TEXTUREDRECTANGLE_H
#define TEXTUREDRECTANGLE_H
#include "utils/vec2.h"
#include "defaults.h"

class GameObject
{
public:
    enum Type {
        GAMEOBJECT,
        SHIP,
        AISHIP,
        CANONBALL
    };

    int width = 100;
    int height = 100;

    Vec2 acceleration;
    Vec2 velocity;
    Vec2 position;
    float friction = 1;

    float angularAcceleration = 0;
    float angularVelocity = 0;
    float angle = 0;
    float angularFriction = 1;

    float maxAngularVelocity = MAXFLOAT;

    uint texture = 0;
    GameObject();
    virtual ~GameObject();
    void setRadialAcceleration(float radialAcceleration);
    void operator=(const GameObject& box);
    static bool colliding(const GameObject &a, const GameObject &b);
    static bool pointInBox(Vec2 &point, GameObject &box);

    Vec2 getDirection() const;

    virtual bool collidesWith(GameObject &object) const;
    virtual void onCollision(const GameObject *object);
    virtual void update(qint64 timeElapsed);

    Type getType() const;
    void setType(const Type &value);

    void setRange(float value);

    void setInitialPosition(const Vec2 &value);

    bool isOutOfRange();
    Vec2 getInitialPosition() const;

    float getRange() const;

    bool isControllable() const;
    void setIsControllable(bool value);


    bool destroyOnCollision() const;
    void setDestroyOnCollision(bool value);

    GameObject *getParent() const;
    void setParent(GameObject *value);

    bool isDangerous() const;
    void setIsDangerous(bool isDangerous);

    int getDamage() const;
    void setDamage(int value);


protected:
    Type type;
private:
    GameObject* parent = NULL;
    unsigned _visibility = 100;
    bool _destroyOnCollision = false;
    bool _isControllable = false;
    bool _isDangerous = false;
    int damage = 10;
    float range = 0;
    Vec2 initialPosition;
    std::vector<Vec2> getAxes() const;
    std::vector<Vec2> getVertices() const;
};

#endif // TEXTUREDRECTANGLE_H
