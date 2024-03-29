#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "worldobjects/ship.h"
#include "utils/vec2.h"
#include "worldobjects/aiship.h"
#include "worldobjects/gameobject.h"
#include "rendering/openglrenderer.h"
#include "rendering/texturedrectangleprogram.h"
#include "rendering/rectangleprogram.h"
#include "worldobjects/gamebutton.h"
#include "worldobjects/camera.h"
#include "message.h"
#include <QKeyEvent>
#include <vector>
#include <unordered_set>

/**
 * @brief The GameWorld class
 * This class acts as a controller, it shouldn't call any opengl
 * functions directly.
 */
class GameWorld
{
public:
    ~GameWorld();
    void init();
    void update();
    void setWind(float magnitude, float angle);
    void renderWorld(int screenHalfWidth, int screenHalfHeight);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void setScreenDimensions(unsigned screenHalfWidth, unsigned screenHalfHeight);
    void handleCollisions();
    long getWorldHeight() const;
    long getWorldWidth() const;
    void sendMessage(Message message);

    void addObject(GameObject *object);
    AIShip *getAIShipAt(unsigned i) const;
    static GameWorld* getInstance();
    static void destroyInstance();
    GameObject *getControllable();
    void onDestroy(GameObject* object);
private:
    void destroyObjects();

    GameWorld();
    static GameWorld* instance;
    Camera camera;
    std::vector<GameObject *> objects;
    std::vector<Message> _messageQueue;
    std::unordered_set<GameObject *> destroyedObjects;
    RectangleProgram rectangleRenderer;
    GameObject windArrow;
    float windAngle;
    GameButton jollyRogerButton;
    GameButton spanishFlagButton;
    GameButton frenchFlagButton;
    GameButton englishFlagButton;
    GameButton noFlagButton;

    unsigned screenHalfWidth = 0;
    unsigned screenHalfHeight = 0;
    qint64 lastFrame = -1;
    long frame = 0;
    float fps = 0;

    int selected = -1;

    Vec2 aiTarget;
    long worldWidth = WORLD_WIDTH;
    long worldHeight = WORLD_HEIGHT;
};

#endif // GAMEWORLD_H
