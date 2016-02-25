//
// Created by cyberxix on 25.02.16.
//

#include "DelayedStarter.h"

DelayedStarter::DelayedStarter(Controller *c, int parent_comm_id, ManualInputId cancel_input_id, Timing timer) {
    this->cancel_input_id = cancel_input_id;
    this->parent_comm_id = parent_comm_id
    comm_id = Message::generateCommunicationId();
    //start Timer
    Message::createTimerRequest(c, getType(), comm_id, timer);
}

ActionType DelayedStarter::getType() {
    return ActionType::DELAYED;
}

void DelayedStarter::onMessage(Controller *c, Message *m) {
    if(m->getType() == MessageType::MANUAL_INPUT_CHANGE
            && m->getValue(MessageField::MANUAL_INPUT_CHANGE__ID) == (int)cancel_input_id
            && m->getValue(MessageField::MANUAL_INPUT_CHANGE__VALUE) == (int)IOState::INACTIVE){

        //dye silently
        c->removeConsumer(this);

    } else if(m->getType() == MessageType::TIMER_STATE
              && m->getCommunicationId() == comm_id){

        //send ok back
        Message::createActionState(c, getType(), parent_comm_id, ActionState::STOPPED_OK);
        c->removeConsumer(this);

    }
}


