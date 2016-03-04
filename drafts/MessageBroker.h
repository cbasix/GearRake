//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MESSAGE_BROKER_H
#define GEARRAKE_MESSAGE_BROKER_H

#include <util.h>
#include "interfaces.h"

//todo write tests
class MessageBroker : public Controller{
private:
    Producer* producer_data[MAX_PRODUCER];//
    Consumer* consumer_data[MAX_CONSUMER];//
    Message message_data[MAX_MSG];

    ArrayList<Producer*> producers = ArrayList<Producer*>(producer_data, MAX_PRODUCER);//
    ArrayList<Consumer*> consumers = ArrayList<Consumer*>(consumer_data, MAX_CONSUMER);//
    CircularQueue<Message> messages = CircularQueue<Message>(message_data, MAX_MSG);


public:
    MessageBroker();
    virtual void registerConsumer(Consumer *c);
    virtual void removeConsumer(Consumer *c);
    virtual void registerProducer(Producer *p);
    virtual void removeProducer(Producer *p);

    virtual ArrayList<Consumer*>*getConsumers();
    virtual ArrayList<Producer*>*getProducers();

    virtual void queueMessage(Message m);

    virtual void runProducers();
    virtual void processMessageQueue();

};



#endif //GEARRAKE_MESSAGE_BROKER_H
