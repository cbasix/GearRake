//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_LOW_H
#define GEARRAKE_LOW_H


#include <interfaces.h>

class Low : public Consumer{
    //todo implement
public:
    Low(Controller *c, int parent_comm_id);
    virtual ActionType getType();

    virtual void onMessage(Controller *c, Message *m);

private:
    int comm_id;
    int parent_comm_id;
};


#endif //GEARRAKE_LOW_H
