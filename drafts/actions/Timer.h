//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_TIMER_H
#define GEARRAKE_TIMER_H

#include "interfaces.h"
#include "constants.h"

#ifdef TESTING
   class ClockWrapper;
#endif


class Timer : public Producer{
public:
    Timer(int parent_communication_id, int time_to_wait, bool is_timeout);
    virtual ActionType getType();
    virtual void produce(Controller *c);

#ifdef TESTING //only usable in test mode
    void setStartTime(unsigned long start_time);
#endif

private:
    int parent_communication_id;
    int time_to_wait;
    bool is_timeout;
    unsigned long start_time;


#ifdef TESTING //only public in test mode
public:
#endif
    ClockWrapper* cw;

};


class ClockWrapper{
public:
    unsigned long getTime();
#ifdef TESTING
    void setReturnValue(unsigned long retv);

private:
    unsigned long retv;
#endif

};



#endif //GEARRAKE_TIMER_H
