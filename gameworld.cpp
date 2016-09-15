#include "gameworld.h"

GameWorld::GameWorld() {}

void GameWorld::update() {
    ship.update();
    for (int i = 0; i < aiships.size(); i++) {
        aiships.at(i).update();
    }
}

void GameWorld::setWind(float magnitude, float angle) {
    ship.setWind(magnitude, angle);
    for (int i = 0; i < aiships.size(); i++) {
        aiships.at(i).setWind(magnitude, angle);
    }
}

void GameWorld::setShip(Ship ship) {
    this->ship = ship;
}

void GameWorld::addAIShip(AIShip ship) {
    aiships.push_back(ship);
}

void GameWorld::setShipRenderer(TexturedRectangleProgram *renderer) {
    shipRenderer = renderer;
}

void GameWorld::setCanonBallRenderer(RectangleProgram *renderer) {
    canonBallRenderer = renderer;
}
