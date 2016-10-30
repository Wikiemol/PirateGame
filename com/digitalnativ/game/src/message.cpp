#include "message.h"

Message::Message(MessageType type) : _type(type) {  }

void Message::setProperty(Message::MessageKey key, MessageProperty *value)
{
    _propertyMap[key] = value;
}

MessageProperty *Message::getValue(Message::MessageKey key)
{
    return _propertyMap[key];
}

long Message::getTimestamp() const
{
    return _timestamp;
}

void Message::setTimestamp(long value)
{
    _timestamp = value;
}

Message::MessageType Message::getType() const
{
    return _type;
}

bool Message::hasProperty(Message::MessageKey key)
{
    return _propertyMap.find(key) != _propertyMap.end();
}
