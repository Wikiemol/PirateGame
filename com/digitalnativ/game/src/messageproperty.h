#ifndef MESSAGEPROPERTY_H
#define MESSAGEPROPERTY_H


class MessageProperty
{
public:
    enum PropertyType {
    };

    virtual PropertyType getType() = 0;
};

#endif // MESSAGEPROPERTY_H
