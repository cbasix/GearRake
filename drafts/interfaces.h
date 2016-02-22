//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_INTERFACES_H
#define GEARRAKE_INTERFACES_H

#include "Message.h"
#include "constants.h"
#include "util.h"

class Controller;
class Message;
class Consumer;
class Producer;

class Action{
public:
    virtual ActionType getType() = 0;
};

class Consumer : public Action{
public:
    virtual void onMessage(Controller* c, Message* m) = 0;
};

class Producer : public Action {
public:
    virtual void produce(Controller* c) = 0;
};

class Controller{
public:
    virtual void registerConsumer(Consumer* c) = 0;
    virtual void removeConsumer(Consumer* c) = 0;
    virtual void registerProducer(Producer* p) = 0;
    virtual void removeProducer(Producer* p) = 0;

    virtual ArrayList<Consumer*>* getConsumer() = 0;
    virtual ArrayList<Producer*>* getProducer() = 0;

    virtual void queueMessage(Message m) = 0;

};

#endif //GEARRAKE_INTERFACES_H


