#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include "gameobject.h"
#include <functional>


class GameButton : public GameObject
{
public:
    GameButton();
    void setAction(std::function<void()> f);
    void actionPerformed();
private:
    std::function<void()> action;
};

#endif // GAMEBUTTON_H
