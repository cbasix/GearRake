//
// Created by cyberxix on 25.02.16.
//

#ifndef GEARRAKE_LED_H
#define GEARRAKE_LED_H


#include <interfaces.h>

class Led : public Consumer{

public:
    Led();
    virtual ActionType getType();

    virtual void onMessage(Controller *c, Message *m);

private:
    int comm_id;
};


#endif //GEARRAKE_LED_H
