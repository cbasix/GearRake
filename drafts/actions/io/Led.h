//
// Created by cyberxix on 25.02.16.
//

#ifndef GEARRAKE_LED_H
#define GEARRAKE_LED_H


#include <interfaces.h>

class Led : public Consumer{

public:
    virtual ActionType getType();

    virtual void onMessage(Controller *c, Message *m);
};


#endif //GEARRAKE_LED_H
