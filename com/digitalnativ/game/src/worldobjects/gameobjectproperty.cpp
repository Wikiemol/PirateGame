#include "gameobjectproperty.h"
#include <QDebug>

GameObjectProperty::GameObjectProperty() {}

GameObjectProperty::GameObjectProperty(const GameObjectProperty &property)
{
    this->name = property.getName();
    this->intValue = property.getValue<int>();
    this->boolValue = property.getValue<bool>();
    this->type = property.getType();
}

GameObjectProperty::GameObjectProperty(PropertyName name, int value)
{
    this->name = name;
    this->intValue = value;
    this->type = INTEGER;
}

GameObjectProperty::GameObjectProperty(GameObjectProperty::PropertyName name, bool value)
{
    this->name = name;
    this->boolValue = value;
    this->type = BOOLEAN;
}

GameObjectProperty::PropertyName GameObjectProperty::getName() const
{
    return name;
}

GameObjectProperty::PropertyType GameObjectProperty::getType() const
{
    return type;
}

int GameObjectProperty::getIntValue() const
{
    return intValue;
}

bool GameObjectProperty::getBoolValue() const
{
    return boolValue;
}

bool GameObjectProperty::operator==(const GameObjectProperty p2) const
{
    return this->getName() == p2.getName();
}

GameObjectProperty GameObjectProperty::key(GameObjectProperty::PropertyName name)
{
    GameObjectProperty key(name);
    return key;
}

GameObjectProperty::GameObjectProperty(GameObjectProperty::PropertyName name)
{
    this->name = name;
}


bool GameObjectProperty::typeCheck(PropertyType type) const {
    if (this->type != type) {
        qDebug() << "GameObjectProperty: Called getXValue on wrong type";
        return false;
    }
    return true;
}
