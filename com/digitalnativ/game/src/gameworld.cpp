#include "gameworld.h"
#include "rendering/renderer.h"
#include "defaults.h"
#include <QDateTime>
#include <unordered_set>
#include <algorithm>

GameWorld::GameWorld() {
}


GameWorld::~GameWorld()
{
    for (unsigned i = 0; i < objects.size(); i++) {
        delete objects.at(i);
    }
}

void GameWorld::update() {
    qint64 timeElapsed = (int) 1000.0 / fps;
    if (lastFrame == -1) {
        timeElapsed = 0;
    }
    for (unsigned i = 0; i < objects.size(); i++) {
        GameObject* object = objects.at(i);
        if (CONTROLLABLE_AI_TARGET && object->getType() == GameObject::AISHIP) {
            AIShip* aiship = static_cast<AIShip*>(object);
            GameObject * controllable = getControllable();
            if (controllable != NULL) {
                aiship->setTarget(*controllable);
            }
        }

        object->update(timeElapsed);
        if (CAMERA_FOLLOWING_PLAYER && object->getType() == GameObject::SHIP) {
            camera.position = object->position;
        }
    }
    handleCollisions();
    destroyObjects();
}

void GameWorld::handleCollisions() {
    for (unsigned obj1Index = 0; obj1Index < objects.size(); obj1Index++) {
        GameObject* object1 = objects.at(obj1Index);
        for (unsigned obj2Index = 0; obj2Index < objects.size(); obj2Index++){
            if (obj2Index == obj1Index) {
                continue;
            }

            GameObject* object2 = objects.at(obj2Index);

            object1->see(object2);

            if (object1->getParent() != object2 && object2->getParent() != object1 &&
                    object1->collidesWith(*object2)) {

                object1->onCollision(object2);
                object2->onCollision(object1);
            }
        }
    }

}

void GameWorld::destroyObjects()
{
    unsigned i = 0;
    for (auto iter = destroyedObjects.begin(); iter != destroyedObjects.end(); iter++) {
        GameObject* object = (*iter);
        delete object;
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
        i++;
    }
    destroyedObjects.clear();
}

void GameWorld::onDestroy(GameObject *object)
{
    destroyedObjects.insert(object);
}

long GameWorld::getWorldHeight() const
{
    return worldHeight;
}

long GameWorld::getWorldWidth() const
{
    return worldWidth;
}

void GameWorld::setWind(float magnitude, float angle)
{
    this->windAngle = angle;
    for (unsigned i = 0; i < objects.size(); i++) {
        if (objects.at(i)->getType() == GameObject::AISHIP || objects.at(i)->getType() == GameObject::SHIP) {
            static_cast<Ship*>(objects.at(i))->setWind(magnitude, angle);
        }
    }
}

void GameWorld::addObject(GameObject *object)
{
    objects.push_back(object);
}

GameObject* GameWorld::getControllable() {
    for (unsigned i = 0; i < objects.size(); i++) {
        if (objects.at(i)->isControllable()) {
            return objects.at(i);
        }
    }
    return NULL;
}


void GameWorld::init() {
    TexturedRectangleProgram::getTexture(":/images/wind_arrow.png", &windArrow.texture);
    TexturedRectangleProgram::getTexture(":/images/flags/roger_flag.png", &jollyRogerButton.texture);
    TexturedRectangleProgram::getTexture(":/images/flags/spanish_flag.png", &spanishFlagButton.texture);
    TexturedRectangleProgram::getTexture(":/images/flags/french_flag.png", &frenchFlagButton.texture);
    TexturedRectangleProgram::getTexture(":/images/flags/english_flag.png", &englishFlagButton.texture);
    TexturedRectangleProgram::getTexture(":/images/flags/no_flag.png", &noFlagButton.texture);

    jollyRogerButton.setAction([this]() {
        GameObject * controllable = getControllable();
        if (controllable != NULL && controllable->getType() == GameObject::SHIP) {
            Ship *ship = static_cast<Ship*>(controllable);
            ship->setFlag(Ship::JOLLY_ROGER);
        }
    });
    frenchFlagButton.setAction([this]() {
        GameObject * controllable = getControllable();
        if (controllable != NULL && controllable->getType() == GameObject::SHIP) {
            Ship *ship = static_cast<Ship*>(controllable);
            ship->setFlag(Ship::FRENCH);
        }
    });
    spanishFlagButton.setAction([this](){
        GameObject * controllable = getControllable();
        if (controllable != NULL && controllable->getType() == GameObject::SHIP) {
            Ship *ship = static_cast<Ship*>(controllable);
            ship->setFlag(Ship::SPANISH);
        }
    });
    englishFlagButton.setAction([this]() {
        GameObject * controllable = getControllable();
        if (controllable != NULL && controllable->getType() == GameObject::SHIP) {
            Ship *ship = static_cast<Ship*>(controllable);
            ship->setFlag(Ship::ENGLISH);
        }
    });
    noFlagButton.setAction([this]() {
        GameObject* controllable = getControllable();
        if (controllable != NULL && controllable->getType() == GameObject::SHIP) {
            Ship *ship = static_cast<Ship*>(controllable);
            ship->setFlag(Ship::NONE);
        }
    });

    GLuint noSailsTex;
    GLuint allSailsTex;
    GLuint mainSailsTex;
    GLuint foreAndAftSailsTex;
    TexturedRectangleProgram::getTexture(":/images/no_sails.png", &noSailsTex);
    TexturedRectangleProgram::getTexture(":/images/all_sails.png", &allSailsTex);
    TexturedRectangleProgram::getTexture(":/images/main_sails.png", &mainSailsTex);
    TexturedRectangleProgram::getTexture(":/images/foreandaft_sails.png", &foreAndAftSailsTex);
    for (int i = 0; i < 1; i++) {
        AIShip *aiship = new AIShip();
        aiship->width = 300;
        aiship->height = 120;
        aiship->position.x = std::rand() % worldWidth - worldWidth / 2.0;
        aiship->position.y = std::rand() % worldHeight - worldHeight / 2.0;
        aiship->setState(AIShip::ATTACK);
        aiship->setTextures(allSailsTex, mainSailsTex, foreAndAftSailsTex, noSailsTex);

        addObject(aiship);
    }
    camera.zoom = 1;
}

void GameWorld::setScreenDimensions(unsigned screenHalfWidth, unsigned screenHalfHeight) {
    this->screenHalfWidth = screenHalfWidth;
    this->screenHalfHeight = screenHalfHeight;
    Renderer::setScreenDimensions(screenHalfWidth, screenHalfHeight);
}

void GameWorld::mousePressEvent(QMouseEvent *event) {
    Vec2 mouse(event->x(), event->y());
    Vec2::subtract(&mouse, Vec2(screenHalfWidth / 2.0, screenHalfHeight / 2.0));
    mouse.y *= -2;
    mouse.x *= 2;
    mouse.y /= camera.zoom;
    mouse.x /= camera.zoom;

    if (GameObject::pointInBox(mouse, frenchFlagButton)) {
        frenchFlagButton.actionPerformed();
        return;
    }
    if (GameObject::pointInBox(mouse, jollyRogerButton)) {
        jollyRogerButton.actionPerformed();
        return;
    }
    if (GameObject::pointInBox(mouse, spanishFlagButton)) {
        spanishFlagButton.actionPerformed();
        return;
    }
    if (GameObject::pointInBox(mouse, englishFlagButton)) {
        englishFlagButton.actionPerformed();
        return;
    }

    if (GameObject::pointInBox(mouse, noFlagButton)) {
        noFlagButton.actionPerformed();
        return;
    }

    Vec2::add(&mouse, camera.position);

    for (int i = 0; i < (int) objects.size(); i++) {
        if (GameObject::pointInBox(mouse, *objects.at(i))) {
            if (selected == i) {
                selected = -1;
            } else {
                selected = i;
            }
            continue;
        }

        AIShip *aiship = getAIShipAt(i);
        if (aiship != NULL) {
            aiship->setTarget(mouse);
        }

    }

}

/**
 * @brief GameWorld::getAIShipAt
 * @param i
 * @return NULL if corresponding object is not an AIShip
 */
AIShip* GameWorld::getAIShipAt(unsigned i) const {
    if (objects.at(i)->getType() == GameObject::AISHIP) {
        return static_cast<AIShip*>(objects.at(i));
    } else {
        return NULL;
    }
}

GameWorld* GameWorld::instance = NULL;
GameWorld* GameWorld::getInstance()
{
    if (instance == NULL) {
        instance = new GameWorld();
    }
    return instance;
}

void GameWorld::destroyInstance()
{
    delete instance;
}


void GameWorld::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    GameObject *object = getControllable();
    if (object != NULL) {
        Controllable* controllable = dynamic_cast<Controllable*>(object);
        if (selected != -1) {
            controllable->keyPressEvent(event, objects.at(selected));
        } else {
            controllable->keyPressEvent(event, NULL);
        }
    }
    switch (event->key()) {
        case Qt::Key_F:
            qDebug() << "Fps: " << fps;
        break;
        case Qt::Key_Escape:
            lastFrame = -1;
        break;
    }
}

void GameWorld::keyReleaseEvent(QKeyEvent* event) {
    GameObject * object = getControllable();
    if (object != NULL) {
        Controllable* controllable = dynamic_cast<Controllable*>(object);
        controllable->keyReleaseEvent(event);
    }
}

void GameWorld::renderWorld(int screenHalfWidth, int screenHalfHeight)
{
    GameObject background;
    background.width = worldWidth;
    background.height = worldHeight;
    TexturedRectangleProgram::getTexture(":/images/water_texture.png", &background.texture);
    Renderer::drawTexturedRect(background);
    Renderer::setCamera(camera);
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 timeElapsed = currentTime - lastFrame;
    if (lastFrame == -1) {
        lastFrame = QDateTime::currentMSecsSinceEpoch();
    } else {
        if (frame == 1 || frame == 100 || frame % 100 == 0) {
            fps = 1000.0 / (double) timeElapsed;
        }
        lastFrame = currentTime;
    }
    frame++;

    for (unsigned i = 0; i < objects.size(); i++) {
        GameObject *object = objects.at(i);
        GameObject::Type type = object->getType();
        if (type == GameObject::AISHIP) {
            Renderer::setColor(128, 128, 128, 128);
            Renderer::drawCircle(object->position, object->getSight());
        }
        if (type == GameObject::AISHIP || objects.at(i)->getType() == GameObject::SHIP) {
            if (selected == (int) i) {
                Renderer::setColor(255, 0, 0, 128);
                Renderer::drawRect(*objects.at(i));
            }
            Ship* ship = static_cast<Ship*>(objects.at(i));
            Renderer::drawShip(*ship, true);
        } else if ((objects.at(i)->getType() == GameObject::CANONBALL)) {
            Renderer::setColor(60, 60, 60, 255);
            Renderer::drawCircle(*objects.at(i));
        }
    }

    for (unsigned i = 0; i < objects.size(); i++) {
        AIShip* aiShip = getAIShipAt(i);
        if (aiShip != NULL) {
            GameObject target;
            target.width = 20;
            target.height = 20;
            target.position = aiShip->getTarget().position;

            Renderer::setColor(128, 128, 255, 128);
            Renderer::drawRect(target);
        }
    }

    windArrow.position.x = screenHalfWidth - screenHalfWidth / 4.0;
    windArrow.position.y = -screenHalfHeight + screenHalfHeight / 4.0;
    windArrow.angle = this->windAngle;
    Renderer::drawMenuIcon(windArrow);

    jollyRogerButton.position.x = - screenHalfWidth + jollyRogerButton.width / 2.0;
    jollyRogerButton.position.y = screenHalfHeight - jollyRogerButton.height / 2.0;
    Renderer::drawMenuIcon(jollyRogerButton);


    spanishFlagButton.position.x = - screenHalfWidth + spanishFlagButton.width / 2.0 + jollyRogerButton.width;
    spanishFlagButton.position.y = screenHalfHeight - spanishFlagButton.height / 2.0;
    Renderer::drawMenuIcon(spanishFlagButton);

    frenchFlagButton.position.x = - screenHalfWidth + frenchFlagButton.width / 2.0 + jollyRogerButton.width * 2;
    frenchFlagButton.position.y = screenHalfHeight - frenchFlagButton.height / 2.0;
    Renderer::drawMenuIcon(frenchFlagButton);

    englishFlagButton.position.x = - screenHalfWidth + englishFlagButton.width / 2.0 + jollyRogerButton.width * 3;
    englishFlagButton.position.y = screenHalfHeight - englishFlagButton.height / 2.0;
    Renderer::drawMenuIcon(englishFlagButton);

    noFlagButton.position.x = - screenHalfWidth + noFlagButton.width / 2.0 + jollyRogerButton.width * 4;
    noFlagButton.position.y = screenHalfHeight - noFlagButton.height / 2.0;
    Renderer::drawMenuIcon(noFlagButton);

}
