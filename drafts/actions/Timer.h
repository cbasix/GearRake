//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_TIMER_H
#define GEARRAKE_TIMER_H

#include "interfaces.h"
#include "constants.h"


class Timer : public Producer{
public:
    Timer(int parent_communication_id, Timing timing, bool is_timeout);
    virtual ActionType getType();
    virtual void produce(Controller *c);

private:
    int parent_communication_id;
    int time_to_wait;
    bool is_timeout;
    unsigned long start_time;

};




#endif //GEARRAKE_TIMER_H
