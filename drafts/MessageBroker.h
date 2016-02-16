//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MESSAGE_BROKER_H
#define GEARRAKE_MESSAGE_BROKER_H

#include <util.h>
#include "interfaces.h"

class MessageBroker : public Controller{
private:
    ArrayList<Consumer*>* consumers;
    ArrayList<Producer*>* producers;
    CircularQueue<Message>* messages;
};



#endif //GEARRAKE_MESSAGE_BROKER_H
