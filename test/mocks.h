//
// Created by cyberxix on 17.02.16.
//

#ifndef GEARRAKE_MOCKS_H
#define GEARRAKE_MOCKS_H


#include "gmock/gmock.h"
#include "interfaces.h"

// Brings in Google Mock.

class MockController : public Controller{
public:
    MOCK_METHOD1(registerConsumer, void(Consumer* c));
    MOCK_METHOD1(removeConsumer, void(Consumer* c));
    MOCK_METHOD1(registerProducer, void(Producer* p));
    MOCK_METHOD1(removeProducer, void(Producer* p));
    MOCK_METHOD1(queueMessage, void(Message m));
};


#endif //GEARRAKE_MOCKS_H
