//
// Created by cyberxix on 24.02.16.
//

#include "Low.h"

ActionType Low::getType() {
    return ActionType::LOW;
}

Low::Low(Controller *c, int parent_comm_id) {
    this->state = LowState::WAITING;
    this->parent_comm_id = parent_comm_id;
    comm_id = Message::generateCommunicationId();
    //start Timer
    Message::createTimerRequest(c, getType(), comm_id, Timing::WAIT_AUTO);
}


void Low::onMessage(Controller *c, Message *m) {
    //todo implement states
    if(m->getType() == MessageType::MANUAL_INPUT_CHANGE
       && m->getValue(MessageField::MANUAL_INPUT_CHANGE__ID) == (int)ManualInputId::AUTO_LOW
       && m->getValue(MessageField::MANUAL_INPUT_CHANGE__VALUE) == (int)IOState::INACTIVE){

        //dye silently if button is released, before start wait time is over
        Message::createActionState(c, getType(), parent_comm_id, ActionState::STOPPED_ERROR);
        c->removeConsumer(this);

    } else if(m->getType() == MessageType::TIMER_STATE
              && m->getCommunicationId() == comm_id){

        Message::createMovePositionRequest(c, getType(), comm_id, CylinderId::FRAME, CylinderPosition::LOW);
        state = LowState::MOVING;
    }

    case LowState::MOVING:
        if (m->getType() == MessageType::ACTION_STATE
                   && m->getCommunicationId() == comm_id){

            //send ok back subtask was successfull
            Message::createActionState(c, getType(), parent_comm_id, ActionState::STOPPED_OK);
            c->removeConsumer(this);

        } else if (m->getType() == MessageType::MANUAL_INPUT_CHANGE
                   && m->getValue(MessageField::MANUAL_INPUT_CHANGE__VALUE) == (int)IOState::ACTIVE){

            //stop if any button is pressed -> cancel subtasks
            Message::createActionState(c, getType(), comm_id, ActionState::STOPPING);


            Message::createActionState(c, getType(), parent_comm_id, ActionState::STOPPED_ERROR);
            c->removeConsumer(this);
        }


}
