#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include "boundingbox.h"
#include "vec2.h"


class Ship : public BoundingBox
{
public:
    Ship();
    void update();
    void setWind(float magnitude, float angle);
    void toggleMainSails();
    void toggleForeAndAftSails();
    void setTextures(uint allSails, uint mainSails, uint foreAndAftSails, uint noSails);
    void fireCanons();
    Vec2 getDirection();
    BoundingBox *getCanonBallAt(int i);
    int getNumberOfCanonBalls();
    void deleteCanon(int i);
private:
    Vec2 wind;
    uint all_sails_tex = 0;
    uint no_sails_tex = 0;
    uint main_sails_tex = 0;
    uint foreandaft_sails_tex = 0;
    bool mainSails = false;
    bool foreAndAftSails = false;
    int numberOfCanons = 20;
    std::vector<BoundingBox> canons;
    qint64 lastCanonFire = -1;
};

#endif // SHIP_H
