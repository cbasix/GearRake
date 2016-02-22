//
// Created by cyberxix on 18.02.16.
//
#include "mocks.h"

void EmptyController::registerConsumer(Consumer *c) {}
void EmptyController::removeConsumer(Consumer *c) {}
void EmptyController::registerProducer(Producer *p) {}
void EmptyController::removeProducer(Producer *p) {}
void EmptyController::queueMessage(Message m) {}

ArrayList<Consumer *> *EmptyController::getConsumer() {}
ArrayList<Producer *> *EmptyController::getProducer() {}
