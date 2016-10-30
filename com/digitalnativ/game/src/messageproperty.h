#ifndef MESSAGEPROPERTY_H
#define MESSAGEPROPERTY_H
#include "gametype.h"


class MessageProperty
{
public:

    virtual bool isType(GType type) const = 0;
    virtual void addType(GType type) = 0;
};

#endif // MESSAGEPROPERTY_H
