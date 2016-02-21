//
// Created by cyberxix on 16.02.16.
//

#include "ConfigStore.h"
#include "FrameDown.h"
#include "constants_message.h"


FrameDown::FrameDown(Controller* c, int parent_communication_id){
    this->parent_communication_id = parent_communication_id;
    state = LocalState::SHORT_FRAME_UP;
    communication_id = Message::createMoveTimeRequest(c, getType(), Cylinder::FRAME, CylinderDirection::UP,
                                                      ConfigStore::getTimerValue(Timing::SHORT));
    timeout_occured = false;

}

void FrameDown::onMessage(Controller* c, Message* m){
    switch (state){
        case LocalState::SHORT_FRAME_UP: //wait for short frame up to finish
            if(m->getType() == MessageType::ACTION_STATE
                    && m->getCommunicationId() == communication_id) {
                state = LocalState::OPEN_LOCK;
                Message::createMovePositionRequest(c, getType(), communication_id, Cylinder::FRAME_LOCK, CylinderPosition::OPEN);
            }
        break;
        case LocalState::OPEN_LOCK: //wait for lock open
            if(m->getType() == MessageType::ACTION_STATE // frame lock open subprocess is done, jea ;)
               && m->getSenderActionType() == ActionType::MOVE_POSITION
               && m->getValue(MessageField::ACTION_STATE__STATE) == (int)(ActionState::STOPPED_OK)
                    && m->getCommunicationId() == communication_id){
                state = LocalState::FRAME_DOWN;
                //start frame down
                Message::createCylinderRequest(c, getType(), communication_id, Cylinder::FRAME, CylinderDirection::DOWN);


            } else if(m->getType() == MessageType::TIMEOUT
                    && m->getCommunicationId() == communication_id){

                state = LocalState::CLOSE_LOCK;
                //close the framelock on timeout
                timeout_occured = true;
                Message::createMovePositionRequest(c, getType(), communication_id, Cylinder::FRAME_LOCK, CylinderPosition::CLOSED);

            }else if(m->getType() == MessageType::ACTION_STATE //parent action sends stop signal
                    && m->getCommunicationId() == parent_communication_id
                     && (int) ActionState::STOPPING ==  m->getValue(MessageField::ACTION_STATE__STATE)){
                state = LocalState::CLOSE_LOCK;
                //close the framelock on stop
                Message::createMovePositionRequest(c, getType(), communication_id, Cylinder::FRAME_LOCK, CylinderPosition::CLOSED);

            }
        break;

        case LocalState::FRAME_DOWN: //wait for end signal
            if(m->getType() == MessageType::ACTION_STATE //parent says: stop it ;)
                    && m->getCommunicationId() == parent_communication_id
                    && m->getValue(MessageField::ACTION_STATE__STATE) == (int) ActionState::STOPPING){

                state = LocalState::CLOSE_LOCK;
                //stop frame movement
                Message::createCylinderRequest(c, getType(),communication_id, Cylinder::FRAME, CylinderDirection::STOP);

                //start close lock
                Message::createMovePositionRequest(c, getType(), communication_id, Cylinder::FRAME_LOCK, CylinderPosition::CLOSED);

            } else if(m->getType() == MessageType::TIMEOUT
                    && m->getCommunicationId() == communication_id){ //got timeout
                state = LocalState::CLOSE_LOCK;

                //stop frame movement
                timeout_occured = true;
                Message::createCylinderRequest(c, getType(),communication_id, Cylinder::FRAME, CylinderDirection::STOP);

                //close the framelock on timeout
                Message::createMovePositionRequest(c, getType(), communication_id, Cylinder::FRAME_LOCK, CylinderPosition::CLOSED);

            }
        break;

        case LocalState::CLOSE_LOCK: //wait for lock close
            if(m->getType() == MessageType::ACTION_STATE // frame lock close is done, jea ;)
               && m->getCommunicationId() == communication_id
               && m->getSenderActionType() == ActionType::MOVE_POSITION
               && m->getValue(MessageField::ACTION_STATE__STATE) == (int)(ActionState::STOPPED_OK)) {

                //send okay message or timeout message to parent
                if (parent_communication_id != 0) {
                    if (timeout_occured) {
                        Message::createTimeout(c, getType(), parent_communication_id, (int)state);
                    } else {
                        Message::createActionState(c, getType(), parent_communication_id, ActionState::STOPPED_OK);
                    }
                }

                c->removeConsumer(this);

            } else if(m->getType() == MessageType::TIMEOUT
                      && m->getCommunicationId() == communication_id){

                //answer to parent with timeout
                Message::createTimeout(c, getType(), parent_communication_id, (int)state);
                c->removeConsumer(this);

            }
        break;

    }
}

ActionType FrameDown::getType() {
    return ActionType::FRAME_DOWN;
}

#ifdef TESTING
void FrameDown::setState(FrameDown::LocalState state){
    this->state = state;
}

void FrameDown::setTimeoutOccured(bool occured) {
    this->timeout_occured = occured;
}

void FrameDown::setCommunicationId(int communication_id) {
    this->communication_id = communication_id;
}

FrameDown::LocalState FrameDown::getState() {
    return state;
}
#endif


