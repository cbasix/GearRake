//
// Created by cyberxix on 22.02.16.
//
#include "MessageBroker.h"
#include "constants.h"
#include "util.h"


void MessageBroker::registerConsumer(Consumer *c) {
    consumers.append(c);
}

void MessageBroker::removeConsumer(Consumer *c) {
    bool is_active_producer = false;
    for (int i = 0; i < producers.getSize(); ++i) {
        if(( Action * )producers.get(i) == ( Action * )c){
            is_active_producer = true;
        }
    }

    for (int j = 0; j < consumers.getSize(); ++j) {
        if(consumers.get(j) == c){
            consumers.remove(j);
            j--; //goto the place of the now deleted element again, because the next elemement is now there
        }
    }

    if(!is_active_producer){

        delete c;
        c = NULL;

    }
}

void MessageBroker::registerProducer(Producer *p) {
    ActionType t = p->getType();
    producers.append(p);
}

void MessageBroker::removeProducer(Producer *p) {
   // test if it is an active consumer so we cant delete it later
    bool is_active_consumer = false;
    for (int i = 0; i < consumers.getSize(); ++i) {
        if(( Action * )consumers.get(i) == ( Action * )p){
            is_active_consumer = true;
        }
    }

    //remove it from the producer array
    for (int j = 0; j < producers.getSize(); ++j) {
        if(producers.get(j) == p){
            producers.remove(j);
            j--; //goto the place of the now deleted element aain, because the next elemement is now there
        }
    }

    //delete it if its not an active consumer
    if(!is_active_consumer){
        delete p;
        p=NULL;
    }
}

void MessageBroker::queueMessage(Message m) {
    messages.add(m);
}

void MessageBroker::runProducers() {
    for (int i = 0; i < producers.getSize(); ++i) {
        Producer* prod = producers.get(i);
        ActionType type = prod->getType();
        prod->produce(this);
    }

}

void MessageBroker::processMessageQueue() {
    if(messages.size() > 0) {
        Message m = messages.get();
        for (int i = 0; i < consumers.getSize(); ++i) {
            consumers.get(i)->onMessage(this, &m);
        }
    }
}

ArrayList<Consumer*>* MessageBroker::getConsumers() {
    return &consumers;
}

ArrayList<Producer*>* MessageBroker::getProducers() {
    return &producers;
}

MessageBroker::MessageBroker() {

}
