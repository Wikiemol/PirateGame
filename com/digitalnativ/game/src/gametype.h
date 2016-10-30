#ifndef GAMETYPE_H
#define GAMETYPE_H
#include <iostream>

enum class GType {
        GAMEOBJECT,
        SHIP,
        AISHIP,
        CANONBALL
};

class GTypeHash {
public:
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

#endif // GAMETYPE_H
