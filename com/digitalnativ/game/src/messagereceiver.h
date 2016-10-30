#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "message.h"
class MessageReceiver {
public:
    virtual void receiveMessage(const Message* message) = 0;
};

#endif // MESSAGERECEIVER_H
