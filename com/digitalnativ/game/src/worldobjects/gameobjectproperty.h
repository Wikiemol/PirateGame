#ifndef GAMEOBJECTPROPERTY_H
#define GAMEOBJECTPROPERTY_H
#include <stdlib.h>
#include <type_traits>
#include <QDebug>


class GameObjectProperty
{

public:
    enum PropertyName {
        WALL,
        DAMAGE
    };

    enum PropertyType {
        INTEGER,
        BOOLEAN
    };

    struct hash {
        size_t operator()(const GameObjectProperty& property) const {
            return property.getType();
        }
    };

    GameObjectProperty();
    GameObjectProperty(const GameObjectProperty &property);
    GameObjectProperty(PropertyName name, int value);
    GameObjectProperty(PropertyName name, bool value);
    PropertyName getName() const;
    PropertyType getType() const;
    bool operator==(const GameObjectProperty p2) const;
    static GameObjectProperty key(PropertyName name);

    template <typename T>
    T getValue() const
    {
        if (std::is_same<T, int>::value) {
            return getIntValue();
        } else if (std::is_same<T, bool>::value) {
            return getBoolValue();
        } else {
            qDebug() << "Type generic not supported for GameObjectProperty::getValue";
        }
    }
private:
    GameObjectProperty(PropertyName name);
    PropertyType type;
    PropertyName name;
    int intValue = 0;
    bool boolValue = false;
    bool typeCheck(PropertyType type) const;
    int getIntValue() const;
    bool getBoolValue() const;
};

#endif // GAMEOBJECTPROPERTY_H
