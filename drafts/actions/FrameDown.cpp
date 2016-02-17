//
// Created by cyberxix on 16.02.16.
//

#include "ConfigStore.h"
#include "FrameDown.h"
#include "constants_message.h"


FrameDown::FrameDown(Controller* c){
    state = LocalState::SHORT_FRAME_UP;
    communication_id = Message::createMoveTimeRequest(c, getType(), Cylinder::FRAME, CylinderDirection::UP, ConfigStore::getTimer(Timing::SHORT));

}

void FrameDown::onMessage(Controller* c, Message* m){
    switch (state){
            case LocalState::SHORT_FRAME_UP: //wait for short frame up to finish
                if(m->getType() ==MessageType::ACTION_STATE
                        && m->getCommunicationId() == communication_id) {
                    state = LocalState::OPEN_LOCK;
                    Message::createMovePositionRequest(c, getType(), communication_id, Cylinder::FRAME_LOCK, CylinderPosition::OPEN);
                }
            break;
            case LocalState::OPEN_LOCK: //wait for lock open
                if(m->getType() ==MessageType::ACTION_STATE){
                    if(m->getValue(MessageField::ACTION_STATE__STATE) == static_cast<int>(ActionState::STOPPED_OK)){
                        state = LocalState::FRAME_DOWN;
                        //start frame down
                        Message::createMoveDirectionRequest(c, getType(), communication_id, Cylinder::FRAME, CylinderDirection::DOWN);

                    }
                } else if(m->getType() ==MessageType::TIMEOUT){
                    state = LocalState::CLOSE_LOCK;
                    //close the framelock on timeout
                    Message::createMovePositionRequest(c, getType(), communication_id, Cylinder::FRAME_LOCK, CylinderPosition::CLOSED);

                }
            break;

            case LocalState::FRAME_DOWN: //wait for end signal to
                /*if(type(PositionNotification)){
                    if(pos.cylinder == Cylinder.getFrameLock()){
                        state = LocalState::FRAME_DOWN;
                        return new MoveToPositionRequest(Cylinder.getFrameLock(), Cylinder.OPEN)
                    }
                } if(type(TimeoutNotification)){
                    state = LocalState::LOCK_CLOSE;
                    Controller.throwError(this, msg, "Timeout beim Warten auf Öffnen des Rahmenschlosses");
                    return new MoveRequest(this, Cylinder.getFrameLock(), Cylinder.CLOSE);
                } else {
                    //ignore all other messages
                    return new EmptyResponse();
                }
            break;

            case LocalState::LOCK_CLOSE: //wait for lock close
                if(type(PositionNotification)){
                    if(pos.cylinder == Cylinder.getFrameLock()){
                        state = LocalState::FRAME_DOWN;
                        return new MoveToPositionRequest(Cylinder.getFrameLock(), Cylinder.OPEN)
                    }
                } if(type(TimeoutNotification)){
                    state = LocalState::LOCK_CLOSE;
                    return new Error(this, msg, "Timeout beim Warten auf Öffnen des Rahmenschlosses");
                } else {
                    //ignore all other messages
                    return new EmptyResponse();
                }
            break;

            case 1:
                if(type(ActionDoneNotification)){

                } else {

                }*/
            break;
    }
}

FrameDown::FrameDown(int parrent_communication_id) {
    this->parrent_communication_id = parrent_communication_id;
}

ActionType FrameDown::getType() {
    return ActionType::FRAME_DOWN;
}


