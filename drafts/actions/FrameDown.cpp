//
// Created by cyberxix on 16.02.16.
//

#include <ConfigStore.h>
#include "FrameDown.h"
#include "constants_message.h"


FrameDown::FrameDown(Controller c){
    state = STATE_SHORT_FRAME_UP;
    communication_id = Message::createMoveTimeRequest(c, getType(), CYLINDER_FRAME, DIRECTION_UP, ConfigStore::getTimer(TIMING_SHORT));

}

void FrameDown::onMessage(Controller c, Message m){
    switch (state){
            case STATE_SHORT_FRAME_UP: //wait for short frame up to finish
                if(m.getType() == MESSAGE_ACTION_STATE
                        && m.getCommunicationId() == communication_id) {
                    state = STATE_OPEN_LOCK;
                    Message::createMovePositionRequest(c, getType(), communication_id, CYLINDER_FRAME_LOCK, POSITION_OPEN);
                }
            break;
            case STATE_OPEN_LOCK: //wait for lock open
                if(m.getType() == MESSAGE_ACTION_STATE){
                    if(m.getValue(MESSAGE_ACTION_STATE__STATE) == ACTION_STATE_STOPPED_OK){
                        state = STATE_FRAME_DOWN;
                        //start frame down
                        Message::createMoveDirectionRequest(c, getType(), communication_id, CYLINDER_FRAME, DIRECTION_DOWN);

                    }
                } else if(m.getType() == MESSAGE_TIMEOUT){
                    state = STATE_CLOSE_LOCK;
                    //close the framelock on timeout
                    Message::createMovePositionRequest(c, getType(), communication_id, CYLINDER_FRAME_LOCK, POSITION_CLOSED);

                }
            break;

            case STATE_FRAME_DOWN: //wait for end signal to
                if(type(PositionNotification)){
                    if(pos.cylinder == Cylinder.getFrameLock()){
                        state = STATE_FRAME_DOWN;
                        return new MoveToPositionRequest(Cylinder.getFrameLock(), Cylinder.OPEN)
                    }
                } if(type(TimeoutNotification)){
                    state = STATE_LOCK_CLOSE;
                    Controller.throwError(this, msg, "Timeout beim Warten auf Öffnen des Rahmenschlosses");
                    return new MoveRequest(this, Cylinder.getFrameLock(), Cylinder.CLOSE);
                } else {
                    //ignore all other messages
                    return new EmptyResponse();
                }
            break;

            case STATE_LOCK_CLOSE: //wait for lock close
                if(type(PositionNotification)){
                    if(pos.cylinder == Cylinder.getFrameLock()){
                        state = STATE_FRAME_DOWN;
                        return new MoveToPositionRequest(Cylinder.getFrameLock(), Cylinder.OPEN)
                    }
                } if(type(TimeoutNotification)){
                    state = STATE_LOCK_CLOSE;
                    return new Error(this, msg, "Timeout beim Warten auf Öffnen des Rahmenschlosses");
                } else {
                    //ignore all other messages
                    return new EmptyResponse();
                }
            break;

            case 1:
                if(type(ActionDoneNotification)){

                } else {

                }
            break;
    }
}

}

FrameDown::FrameDown(int parrent_communication_id) {
    this->parrent_communication_id = parrent_communication_id;
}

ActionType FrameDown::getType() {
    return ACTION_FRAME_DOWN;
}


