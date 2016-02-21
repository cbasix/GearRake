//
// Created by cyberxix on 16.02.16.
//

#include "Timer.h"
#ifndef TESTING //only include ardino.h on arduino
#include "Arduino.h"
#endif

Timer::Timer(int parent_communication_id, int time_to_wait, bool is_timeout) {
    this->parent_communication_id = parent_communication_id;
    this->time_to_wait = time_to_wait;
    this->is_timeout = is_timeout;
    this->cw = new ClockWrapper();
    this->start_time = cw->getTime();
}

ActionType Timer::getType() {
    return ActionType::TIMER;
}

void Timer::produce(Controller *c) {
    //if wait time is over
    if(start_time + time_to_wait < cw->getTime()){
        if(is_timeout) {
            Message::createTimeout(c, getType(), parent_communication_id, 0);
        } else {
            Message::createTimerState(c, getType(), parent_communication_id);
        }
        c->removeProducer(this);
    }
}

#ifdef TESTING //only usable in test mode
void Timer::setStartTime(unsigned long start_time){
    this->start_time = start_time;
}

void ClockWrapper::setReturnValue(unsigned long retv){
    this->retv = retv;
}
#endif


unsigned long ClockWrapper::getTime() {
#ifdef TESTING
    return retv;
#endif
#ifndef TESTING
    return millis();
#endif
}
