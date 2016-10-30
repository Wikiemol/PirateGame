#ifndef MESSAGE_H
#define MESSAGE_H
#include "messageproperty.h"
#include <unordered_map>


class Message
{
public:
    enum MessageKey {
    };
    enum MessageType {
    };

    Message(MessageType type);
    void setProperty(MessageKey key, MessageProperty *value);
    MessageProperty *getValue(MessageKey key);
    long getTimestamp() const;
    void setTimestamp(long value);
    MessageType getType() const;

    bool hasProperty(Message::MessageKey key);
private:
    std::unordered_map<MessageKey, MessageProperty*, std::hash<int>> _propertyMap;
    long _timestamp = 0;
    MessageType _type;
};

#endif // MESSAGE_H
