#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include "gameobject.h"
#include "vec2.h"
#include "collidable.h"
#include "defaults.h"
#include "controllable.h"
#include <QKeyEvent>
class Ship : public GameObject, public Controllable
{
public:
    enum Flag {JOLLY_ROGER, SPANISH, FRENCH, ENGLISH};
    Ship();
    void setWind(float magnitude, float angle);
    void setWind(Vec2 value);
    void toggleMainSails();
    void toggleForeAndAftSails();
    void setTextures(uint allSails, uint mainSails, uint foreAndAftSails, uint noSails);
    void fireCanons();
    GameObject *getCanonBallAt(int i);
    int getNumberOfCanonBalls();
    void removeCanonBallAt(int i);
    void update(qint64 timeElapsed);
    void setFlag(const Flag &value);
    Flag getFlag() const;

    void fireCanons(Vec2 target);
    bool getMainSails() const;
    void setMainSails(bool value);

    bool getForeAndAftSails() const;
    void setForeAndAftSails(bool value);
    void operator=(const Ship &s);

    int getMaxhealth() const;
    void setMaxhealth(int value);

    int getHealth() const;
    void setHealth(int value);

    qint64 getLastCanonFire() const;

    void keyPressEvent(QKeyEvent* event, const GameObject *selected);
    void keyReleaseEvent(QKeyEvent *event);

    void onCollision(const GameObject *object);
protected:
    Vec2 getLiftAcc(Vec2 direction);
    Vec2 wind;
private:
    uint all_sails_tex = 0;
    uint no_sails_tex = 0;
    uint main_sails_tex = 0;
    uint foreandaft_sails_tex = 0;
    bool mainSails = false;
    bool foreAndAftSails = false;
    int numberOfCanons = 5;
    std::vector<GameObject> canonBalls;
    qint64 lastCanonFire = -1;
    Flag flag = JOLLY_ROGER;
    int maxhealth = MAX_HEALTH;
    int health = maxhealth;
};

#endif // SHIP_H
