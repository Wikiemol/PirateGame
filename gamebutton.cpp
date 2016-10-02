#include "gamebutton.h"

GameButton::GameButton() { }

void GameButton::setAction(std::function<void()> f) {
    action = f;
}

void GameButton::actionPerformed() {
    action();
}

