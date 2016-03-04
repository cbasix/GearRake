//
// Created by cyberxix on 25.02.16.
//

#include "Led.h"

ActionType Led::getType() {
    return ActionType::LED ;
}

void Led::onMessage(Controller *c, Message *m) {
    if(m->getType() == MessageType::SENSOR_INPUT_CHANGE
            && m->getValue(MessageField::SENSOR_INPUT_CHANGE__ID) == (int)SensorInputId::FRAME_LOCK_CLOSED){

        IOState led_state = IOState::ACTIVE;
        if((IOState) m->getValue(MessageField::SENSOR_INPUT_CHANGE__VALUE) == IOState::ACTIVE){
            //led off when framelock closed
            led_state = IOState::INACTIVE;
        } else {
            //led on when framelock not closed
            led_state = IOState::ACTIVE;
        }
        Message::createLedRequest(c, getType(), comm_id, OutputId::LED_FRAME_LOCK, led_state);
    }

    if(m->getType() == MessageType::SENSOR_INPUT_CHANGE
            && m->getValue(MessageField::SENSOR_INPUT_CHANGE__ID) == (int)SensorInputId::WEEL_TRACK_MIDDLE){

        IOState led_state = IOState::ACTIVE;
        if((IOState) m->getValue(MessageField::SENSOR_INPUT_CHANGE__VALUE) == IOState::ACTIVE){
            //Message::createLedRequest(ON)
        } else {
            //Message::createLedRequest(OFF)
        }
        Message::createLedRequest(c, getType(), comm_id, OutputId::LED_WEEL_TRACK_MIDDLE, led_state);
    }
}

Led::Led() {
    comm_id = Message::generateCommunicationId();
}
