//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_LOW_H
#define GEARRAKE_LOW_H


#include <interfaces.h>

class Low : public Consumer{
    //todo auto tasks can only start, when no other "work" task is running
public:
    Low(Controller *c, int parent_comm_id);
    virtual ActionType getType();

    virtual void onMessage(Controller *c, Message *m);

private:
    enum class LowState {WAITING, MOVING, ENUM_COUNT};
    int comm_id;
    int parent_comm_id;
    LowState state;
};


#endif //GEARRAKE_LOW_H
