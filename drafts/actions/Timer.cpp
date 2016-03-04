//
// Created by cyberxix on 16.02.16.
//

#include <ConfigStore.h>
#include "Timer.h"
#include "wrapper.h"

//todo possability to stop timer?
Timer::Timer(int parent_communication_id, Timing timing, bool is_timeout) {
    this->parent_communication_id = parent_communication_id;
    this->time_to_wait = ConfigStore::getTimerValue(timing);
    this->is_timeout = is_timeout;
    this->start_time = ClockWrapper::getTime();
}

ActionType Timer::getType() {
    return ActionType::TIMER;
}

void Timer::produce(Controller *c) {
    //if wait time is over
    if(start_time + time_to_wait < ClockWrapper::getTime()){
        if(is_timeout) {
            Message::createTimeout(c, getType(), parent_communication_id, 0);
        } else {
            Message::createTimerState(c, getType(), parent_communication_id);
        }
        c->removeProducer(this);
    }
}



