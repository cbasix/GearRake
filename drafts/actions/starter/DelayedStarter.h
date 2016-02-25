//
// Created by cyberxix on 25.02.16.
//

#ifndef GEARRAKE_DELAYED_H
#define GEARRAKE_DELAYED_H


#include <interfaces.h>

class DelayedStarter : public Consumer {

public:
    DelayedStarter(Controller* c,int parent_comm_id, ManualInputId cancel_input_id, Timing timer);
    virtual ActionType getType();

    virtual void onMessage(Controller *c, Message *m);

private:
    int comm_id;
    ManualInputId cancel_input_id;
    int parent_comm_id;
};


#endif //GEARRAKE_DELAYED_H
