//
// Created by cyberxix on 16.02.16.
//

#include "Move.h"
#include "constants.h"
#include "constants_message.h"
#include "ConfigStore.h"


ActionType Move::getType() {
    return ACTION_MOVE;
}

void Move::onMessage(Controller c, Message m) {
    if(m.getType() == MESSAGE_POSITION_CHANGED // stop when given position is reached
            && position = m.getValue(MVALUE_POSITION)){
        Message::createCylinderRequest(c, getType(), cylinder, DIRECTION_STOP, POSITION_NONE);

        if(parent_communication_id != 0){
            Message::createActionState(c, getType(), parent_communication_id, ACTION_STATE_STOPPED_OK);
        }

    } else if(m.getType() == MESSAGE_VALUE_CHANGED_MANUAL //stop when in mixed or manual mode the input button is released
            && direction != DIRECTION_NONE
            && ACTIVE = m.getValue(MVALUE_STATE)){
        Message::createCylinderRequest(c, getType(), cylinder, DIRECTION_STOP);

        if(parent_communication_id != 0) {
            Message::createActionState(c, getType(), parent_communication_id, ACTION_STATE_STOPPED_OK);
        }

    } if(m.getType() == MESSAGE_TIMEOUT_OCCURED // if timeout occurs
            && m.getCommunicationId() == timeout_communication_id){
        Message::createCylinderRequest(c, getType(), cylinder, DIRECTION_STOP);


        //if started by other Action forward the timeout to it
        if(parent_communication_id != 0){
            Message::createTimeout(c, getType(), parent_communication_id);
        }

    } if(m.getType() == MESSAGE_TIMER_OVER // if timer is over
             && m.getCommunicationId() == timer_communication_id){
        Message::createCylinderRequest(c, getType(), cylinder, DIRECTION_STOP);


        //if started by other Action forward the timeout to it
        if(parent_communication_id != 0){
            Message::createTimeout(c, getType(), parent_communication_id);
        }

    }
}

Move::Move(Controller c, Cylinder cylinder, CylinderPosition position, CylinderDirection direction, int parent_communication_id, int stop_after_timer) {
    this->parent_communication_id = parent_communication_id;
    this->cylinder = cylinder;
    this->direction = direction;
    this->position = position;

    //if direction is given -> manual(move until released) or mixed mode(move until released or position reached)
    //if not given -> automatic mode -> we need to activate timeouts
    if(direction != DIRECTION_NONE) {
        //save the communication id, when timeout occurs this communication id is send back
        timeout_communication_id = Message::createTimeoutRequest(c, getType(), ConfigStore::getTimeout(position));
    }
    //timer mode for short_up and so on.
    if(stop_after_timer != 0){
        //save the communication id, when timer occurs this communication id is send back
        timer_communication_id = Message::createTimerRequest(c, getType(), stop_after_timer);
    }
    //start moving cylinder
    Message::createCylinderRequest(c, getType(), cylinder, direction);

}
