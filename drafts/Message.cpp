//
// Created by cyberxix on 16.02.16.
//

#include "Message.h"
#include "constants_message.h"

MessageTypes Message::getType() {
    return type;
}

int Message::getValue(MessageFields field) {
    return data[field];
}

void Message::setValue(MessageFields field, int value) {
    data[field] = value;
}

int Message::getCommunicationId() {
    return communication_id;
}

int Message::generateCommunicationId() {
    int com_id = next_generated_communication_id++; //post increment
    return com_id;
}

int Message::createTimeoutRequest(Controller c, ActionType type, int timeout) {
    int com_id = generateCommunicationId();
    createTimeoutRequest(c, type, com_id, timeout);
    return com_id;
}

void Message::createTimeoutRequest(Controller c, ActionType type, int communication_id, int timeout) {
    Message m;
    m.type = MESSAGE_TIMOUT_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MESSAGE_TIMEOUT_REQUEST__TIMEOUT, timeout);
    c.queueMessage(m);
}

int Message::createTimerRequest(Controller c, ActionType type, int stop_after) {
    int com_id = generateCommunicationId();
    createTimerRequest(c, type, com_id, stop_after);
    return com_id;
}

void Message::createTimerRequest(Controller c, ActionType type, int communication_id, int stop_after) {
    Message m;
    m.type = MESSAGE_TIMER_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MESSAGE_TIMER_REQUEST__STOP_AFTER, stop_after);
    c.queueMessage(m);
}

int Message::createCylinderRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction) {
    int com_id = generateCommunicationId();
    createCylinderRequest(c, type, com_id, cylinder, direction);
    return com_id;
}

void Message::createCylinderRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder,
                                    CylinderDirection direction) {
    Message m;
    m.type = MESSAGE_CYLINDER_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MESSAGE_CYLINDER_REQUEST__CYLINDER, cylinder);
    m.setValue(MESSAGE_CYLINDER_REQUEST__DIRECTION, direction);
    c.queueMessage(m);
}

int Message::createMoveTimeRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction,
                                   int timer) {
    int com_id = generateCommunicationId();
    createMoveTimeRequest(c, type, com_id, cylinder, direction, timer);
    return com_id;
}

void Message::createMoveTimeRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder,
                                    CylinderDirection direction, int timer) {
    Message m;
    m.type = MESSAGE_MOVE_TIME_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MESSAGE_MOVE_TIME_REQUEST__CYLINDER, cylinder);
    m.setValue(MESSAGE_MOVE_TIME_REQUEST__DIRECTION, direction);
    m.setValue(MESSAGE_MOVE_TIME_REQUEST__TIMER, timer);
    c.queueMessage(m);
}

int Message::createMovePositionRequest(Controller c, ActionType type, Cylinder cylinder, CylinderPosition position) {
    int com_id = generateCommunicationId();
    createMovePositionRequest(c, type, com_id, cylinder, position);
    return com_id;
}

void Message::createMovePositionRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder,
                                       CylinderPosition position) {
    Message m;
    m.type = MESSAGE_MOVE_POSITION_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MESSAGE_MOVE_POSITION_REQUEST__CYLINDER, cylinder);
    m.setValue(MESSAGE_MOVE_POSITION_REQUEST__POSITION, position);
    c.queueMessage(m);
}

int Message::createMoveDirectionRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction) {
    int com_id = generateCommunicationId();
    createMoveDirectionRequest(c, type, com_id, cylinder, direction);
    return com_id;
}

void Message::createMoveDirectionRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder,
                                         CylinderDirection direction) {
    Message m;
    m.type = MESSAGE_MOVE_DIRECTION_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MESSAGE_MOVE_DIRECTION_REQUEST__CYLINDER, cylinder);
    m.setValue(MESSAGE_MOVE_DIRECTION_REQUEST__DIRECTION, direction);
    c.queueMessage(m);
}

void Message::createActionState(Controller c, ActionType type, int parent_communication_id, ActionState state) {
    Message m;
    m.type = MESSAGE_ACTION_STATE;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    m.setValue(MESSAGE_ACTION_STATE__STATE, state);
    c.queueMessage(m);
}

void Message::createTimeout(Controller c, ActionType type, int parent_communication_id) {
    Message m;
    m.type = MESSAGE_TIMEOUT;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    c.queueMessage(m);
}

void Message::createTimerState(Controller c, ActionType type, int parent_communication_id) {
    Message m;
    m.type = MESSAGE_TIMER_STATE;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    c.queueMessage(m);
}

void Message::createPositionState(Controller c, ActionType type, Cylinder cylinder, CylinderPosition position) {
    Message m;
    m.type = MESSAGE_POSITION_STATE;
    m.communication_id = 0;
    m.sender_action_type = type;
    m.setValue(MESSAGE_POSITION_STATE__CYLINDER, cylinder);
    m.setValue(MESSAGE_POSITION_STATE__POSITION, position);
    c.queueMessage(m);
}

Message::Message() {
    type = MESSAGE_NONE;
    communication_id = 0;
    for(int i = 0; i < CONF_MESSAGE_LEN; i++){
        data[i] = 0;
    }

}
