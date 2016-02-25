//
// Created by cyberxix on 16.02.16.
//

#include "Move.h"
#include "constants.h"
#include "constants_message.h"
#include "ConfigStore.h"

MovePosition::MovePosition(Controller* c, int parent_communication_id, CylinderId cylinder, CylinderPosition position) {
    this->parent_communication_id = parent_communication_id;
    this->cylinder = cylinder;
    this->position = position;

    //save the communication id, when timeout occurs this communication id is send back
    communication_id = Message::createTimeoutRequest(c, getType(), ConfigStore::getTimeoutValue(position));

    //get the direction to move to
    Message::createPositionRequest(c, getType(), communication_id, cylinder);
}

ActionType MovePosition::getType() {
    return ActionType::MOVE_POSITION;
}

void MovePosition::onMessage(Controller* c, Message* m) {

    if (m->getType() == MessageType::POSITION_STATE // start moving the cylinder when direction is known
            && m->getCommunicationId() == communication_id
            && m->getValue(MessageField::POSITION_STATE__CYLINDER) == (int)cylinder) {
        CylinderPosition current_position = (CylinderPosition)(m->getValue(MessageField::POSITION_STATE__POSITION));

        if(current_position < position) {
            direction = CylinderDirection::UP;
            Message::createCylinderRequest(c, getType(), communication_id, cylinder, direction);

        } else if(current_position > position) {
            direction = CylinderDirection::DOWN;
            Message::createCylinderRequest(c, getType(), communication_id, cylinder, direction);

        } else {
            if (parent_communication_id != 0) {
                Message::createActionState(c, getType(), parent_communication_id,ActionState::STOPPED_OK);
            }
            //end
            c->removeConsumer(this);
        }



    } else if (m->getType() == MessageType::POSITION_CHANGE // stop when given position is reached
                && (int)cylinder == m->getValue(MessageField::POSITION_STATE__CYLINDER)) {

        if(
                (
                    direction == CylinderDirection::UP
                    && (int)position >= m->getValue(MessageField::POSITION_CHANGE__POSITION)
                ) || (
                    direction == CylinderDirection::DOWN
                    && (int)position <= m->getValue(MessageField::POSITION_CHANGE__POSITION)
                )) {

            Message::createCylinderRequest(c, getType(), cylinder, CylinderDirection::STOP);

            if (parent_communication_id != 0) {
                Message::createActionState(c, getType(), parent_communication_id, ActionState::STOPPED_OK);
            }
            //end
            c->removeConsumer(this);
        }

    } else if (m->getType() == MessageType::ACTION_STATE//stop when in stop signal from parent is send
               && parent_communication_id == m->getCommunicationId()
               && (int)ActionState::STOPPING == m->getValue(MessageField::ACTION_STATE__STATE)) {
        Message::createCylinderRequest(c, getType(), communication_id, cylinder, CylinderDirection::STOP);

        if (parent_communication_id != 0) {
            Message::createActionState(c, getType(), parent_communication_id,ActionState::STOPPED_OK);
        }
        //end
        c->removeConsumer(this);

    } else if (m->getType() == MessageType::TIMEOUT // if timeout occurs
            && m->getCommunicationId() == communication_id) {
        Message::createCylinderRequest(c, getType(), communication_id, cylinder, CylinderDirection::STOP);


        //if started by other Action forward the timeout to it
        if (parent_communication_id != 0) {
            Message::createTimeout(c, getType(), parent_communication_id, 0);
        }
        //end
        c->removeConsumer(this);

    // stop quietly if another task on the same cylinder has started
    } else if (
            (
                m->getType() == MessageType::MOVE_POSITION_REQUEST
                && m->getValue(MessageField::MOVE_POSITION_REQUEST__CYLINDER) == (int)cylinder
            ) || (
                m->getType() == MessageType::MOVE_DIRECTION_REQUEST
                && m->getValue(MessageField::MOVE_DIRECTION_REQUEST__CYLINDER) == (int)cylinder
            ) || (
                 m->getType() == MessageType::MOVE_TIME_REQUEST
                 && m->getValue(MessageField::MOVE_TIME_REQUEST__CYLINDER) == (int)cylinder
            )
    ) {
        //if started by other Action forward the stopping
        if (parent_communication_id != 0) {
            Message::createActionState(c, getType(), parent_communication_id, ActionState::STOPPED_OK);
        }
        //end
        c->removeConsumer(this);

    }
}


MoveTime::MoveTime(Controller* c, int parent_communication_id, CylinderId cylinder, CylinderDirection direction, Timing timer) {
    this->parent_communication_id = parent_communication_id;
    this->cylinder = cylinder;

    //bushit input dont to anything. instant ready ...
    if(direction == CylinderDirection::NONE){
        Message::createActionState(c, getType(), parent_communication_id,ActionState::STOPPED_OK);
        c->removeConsumer(this);
        return;
    }

    //save the communication id, when timer occurs this communication id is send back
    communication_id = Message::createTimerRequest(c, getType(), timer);
    //start moving cylinder
    Message::createCylinderRequest(c, getType(), communication_id, cylinder, direction);

}

ActionType MoveTime::getType() {
    return ActionType::MOVE_TIME;
}

void MoveTime::onMessage(Controller* c, Message* m) {
    if(m->getType() == MessageType::ACTION_STATE//stop when in stop signal is send
              && (int)ActionState::STOPPING == m->getValue(MessageField::ACTION_STATE__STATE)){
        Message::createCylinderRequest(c, getType(), communication_id, cylinder, CylinderDirection::STOP);

        if(parent_communication_id != 0) {
            Message::createActionState(c, getType(), parent_communication_id,ActionState::STOPPED_OK);
        }

        c->removeConsumer(this);

    } if(m->getType() == MessageType::TIMER_STATE // if timer is over
         && m->getCommunicationId() == communication_id){
        Message::createCylinderRequest(c, getType(), communication_id, cylinder, CylinderDirection::STOP);

        //if started by other Action forward send the ready message
        if(parent_communication_id != 0){
            Message::createActionState(c, getType(), parent_communication_id,ActionState::STOPPED_OK);
        }

        c->removeConsumer(this);

    }
}


MoveDirection::MoveDirection(Controller* c, int parent_communication_id, CylinderId cylinder, CylinderDirection direction, bool instant_quit) {
    this->parent_communication_id = parent_communication_id;
    this->cylinder = cylinder;
    this->direction = direction;

    //bushit input dont to anything. instant ready ...
    if(direction == CylinderDirection::NONE){
        Message::createActionState(c, getType(), parent_communication_id, ActionState::STOPPED_OK);
        c->removeConsumer(this);
        return;
    }

    //start moving in given direction
    communication_id = Message::createCylinderRequest(c, getType(), cylinder, direction);

    if(instant_quit){
        if(parent_communication_id != 0) {
            Message::createActionState(c, getType(), parent_communication_id,ActionState::STOPPED_OK);
        }
        c->removeConsumer(this);
    }
}

ActionType MoveDirection::getType() {
    return ActionType::MOVE_DIRECTION;
}

void MoveDirection::onMessage(Controller* c, Message* m) {
    if(m->getType() == MessageType::ACTION_STATE//stop when in stop signal is send
              && direction != CylinderDirection::NONE
              && (int)ActionState::STOPPING == m->getValue(MessageField::ACTION_STATE__STATE)){
        Message::createCylinderRequest(c, getType(), communication_id, cylinder, CylinderDirection::STOP);

        if(parent_communication_id != 0) {
            Message::createActionState(c, getType(), parent_communication_id,ActionState::STOPPED_OK);
        }
        c->removeConsumer(this);
    }
}


