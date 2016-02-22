//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MESSAGE_BROKER_H
#define GEARRAKE_MESSAGE_BROKER_H

#include <util.h>
#include "interfaces.h"

class MessageBroker : public Controller{
private:
public:
    virtual void registerConsumer(Consumer *c);
    virtual void removeConsumer(Consumer *c);
    virtual void registerProducer(Producer *p);
    virtual void removeProducer(Producer *p);
    virtual void queueMessage(Message m);

    virtual void generateActiveMessages();

    ArrayList<Consumer*>* consumers;
    ArrayList<Producer*>* producers;
    CircularQueue<Message>* messages;
};



#endif //GEARRAKE_MESSAGE_BROKER_H
