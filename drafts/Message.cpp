//
// Created by cyberxix on 16.02.16.
//

#include "Message.h"
#include "constants.h"
#include "constants_message.h"


MessageType Message::getType() {
    return type;
}

int Message::next_generated_communication_id = 1;

int Message::getValue(MessageField field) {
    return data[static_cast<int>(field)];
}

void Message::setValue(MessageField field, int value) {
    data[static_cast<int>(field)] = value;
}

void Message::setCommunicationId(int communication_id) {
    this->communication_id = communication_id;
}

void Message::setSenderActionType(const ActionType &sender_action_type) {
    this->sender_action_type = sender_action_type;
}

void Message::setType(const MessageType &type) {
    this->type = type;
}

int Message::getCommunicationId() {
    return communication_id;
}

int Message::generateCommunicationId() {
    int com_id = next_generated_communication_id++; //post increment
    return com_id;
}

int Message::createTimeoutRequest(Controller* c, ActionType type, int timeout) {
    int com_id = generateCommunicationId();
    createTimeoutRequest(c, type, com_id, timeout);
    return com_id;
}

void Message::createTimeoutRequest(Controller* c, ActionType type, int communication_id, int timeout) {
    Message m;
    m.type = MessageType::TIMEOUT_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::TIMEOUT_REQUEST__TIMEOUT, timeout);
    c->queueMessage(m);
}

int Message::createTimerRequest(Controller* c, ActionType type, Timing timer) {
    int com_id = generateCommunicationId();
    createTimerRequest(c, type, com_id, timer);
    return com_id;
}

void Message::createTimerRequest(Controller* c, ActionType type, int communication_id, Timing timer) {
    Message m;
    m.type = MessageType::TIMER_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::TIMER_REQUEST__STOP_AFTER, (int)timer);
    c->queueMessage(m);
}

int Message::createCylinderRequest(Controller* c, ActionType type, Cylinder cylinder, CylinderDirection direction) {
    int com_id = generateCommunicationId();
    createCylinderRequest(c, type, com_id, cylinder, direction);
    return com_id;
}

void Message::createCylinderRequest(Controller* c, ActionType type, int communication_id, Cylinder cylinder,
                                    CylinderDirection direction) {
    Message m;
    m.type = MessageType::CYLINDER_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::CYLINDER_REQUEST__CYLINDER, static_cast<int>(cylinder));
    m.setValue(MessageField::CYLINDER_REQUEST__DIRECTION, static_cast<int>(direction));
    c->queueMessage(m);
}

int Message::createMoveTimeRequest(Controller* c, ActionType type, Cylinder cylinder, CylinderDirection direction,
                                   int timer) {
    int com_id = generateCommunicationId();
    createMoveTimeRequest(c, type, com_id, cylinder, direction, timer);
    return com_id;
}

void Message::createMoveTimeRequest(Controller* c, ActionType type, int communication_id, Cylinder cylinder,
                                    CylinderDirection direction, int timer) {
    Message m;
    m.type = MessageType::MOVE_TIME_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::MOVE_TIME_REQUEST__CYLINDER, static_cast<int>(cylinder));
    m.setValue(MessageField::MOVE_TIME_REQUEST__DIRECTION, static_cast<int>(direction));
    m.setValue(MessageField::MOVE_TIME_REQUEST__TIMER, timer);
    c->queueMessage(m);
}

int Message::createMovePositionRequest(Controller* c, ActionType type, Cylinder cylinder, CylinderPosition position) {
    int com_id = generateCommunicationId();
    createMovePositionRequest(c, type, com_id, cylinder, position);
    return com_id;
}

void Message::createMovePositionRequest(Controller* c, ActionType type, int communication_id, Cylinder cylinder,
                                       CylinderPosition position) {
    Message m;
    m.type = MessageType::MOVE_POSITION_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::MOVE_POSITION_REQUEST__CYLINDER, static_cast<int>(cylinder));
    m.setValue(MessageField::MOVE_POSITION_REQUEST__POSITION, static_cast<int>(position));
    c->queueMessage(m);
}

int Message::createMoveDirectionRequest(Controller* c, ActionType type, Cylinder cylinder, CylinderDirection direction) {
    int com_id = generateCommunicationId();
    createMoveDirectionRequest(c, type, com_id, cylinder, direction);
    return com_id;
}

void Message::createMoveDirectionRequest(Controller* c, ActionType type, int communication_id, Cylinder cylinder,
                                         CylinderDirection direction) {
    Message m;
    m.type = MessageType::MOVE_DIRECTION_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::MOVE_DIRECTION_REQUEST__CYLINDER, static_cast<int>(cylinder));
    m.setValue(MessageField::MOVE_DIRECTION_REQUEST__DIRECTION, static_cast<int>(direction));
    c->queueMessage(m);
}

int Message::createPositionRequest(Controller *c, ActionType type, Cylinder cylinder) {
    int com_id = generateCommunicationId();
    createPositionRequest(c, type, com_id, cylinder);
    return com_id;
}

void Message::createPositionRequest(Controller *c, ActionType type, int communication_id, Cylinder cylinder) {
    Message m;
    m.type = MessageType::POSITION_REQUEST;
    m.communication_id = communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::POSITION_REQUEST__CYLINDER, static_cast<int>(cylinder));
    c->queueMessage(m);
}

void Message::createActionState(Controller* c, ActionType type, int parent_communication_id, ActionState state) {
    Message m;
    m.type = MessageType::ACTION_STATE;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::ACTION_STATE__STATE, static_cast<int>(state));
    c->queueMessage(m);
}

void Message::createTimeout(Controller* c, ActionType type, int parent_communication_id, int state) {
    Message m;
    m.type = MessageType::TIMEOUT;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::TIMEOUT__STATE, state);
    c->queueMessage(m);
}

void Message::createTimerState(Controller* c, ActionType type, int parent_communication_id) {
    Message m;
    m.type = MessageType::TIMER_STATE;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    c->queueMessage(m);
}

void Message::createPositionState(Controller* c, ActionType type, int parent_communication_id, Cylinder cylinder, CylinderPosition position) {
    Message m;
    m.type = MessageType::POSITION_STATE;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::POSITION_STATE__CYLINDER, static_cast<int>(cylinder));
    m.setValue(MessageField::POSITION_STATE__POSITION, static_cast<int>(position));
    c->queueMessage(m);
}

void Message::createPositionChange(Controller* c, ActionType type, int parent_communication_id, Cylinder cylinder,
                                   CylinderPosition position) {
    Message m;
    m.type = MessageType::POSITION_CHANGE;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::POSITION_CHANGE__CYLINDER, static_cast<int>(cylinder));
    m.setValue(MessageField::POSITION_CHANGE__POSITION, static_cast<int>(position));
    c->queueMessage(m);
}

void Message::createInputChange(Controller* c, ActionType type, int parent_communication_id, Cylinder cylinder,
                                CylinderPosition position) {
    Message m;
    m.type = MessageType::INPUT_CHANGE;
    m.communication_id = parent_communication_id;
    m.sender_action_type = type;
    m.setValue(MessageField::INPUT_CHANGE__CYLINDER, static_cast<int>(cylinder));
    m.setValue(MessageField::INPUT_CHANGE__POSITION, static_cast<int>(position));
    c->queueMessage(m);
}

ActionType Message::getSenderActionType() {
    return sender_action_type;
}

Message::Message(MessageType type, ActionType sender_action_type, int communication_id){
    this->type = type;
    this->sender_action_type = sender_action_type;
    this->communication_id = communication_id;

    for(int i = 0; i < (int)MessageField::ENUM_COUNT ; i++){
        data[i] = 0;
    }
}

#ifdef TESTING
bool Message::operator==(const Message& rhs)
{
    if(this->type == rhs.type
           && this->communication_id == rhs.communication_id
           && this->sender_action_type == rhs.sender_action_type){

        for(int i = 0; i < (int)MessageField::ENUM_COUNT; i++){
            if(this->data[i] != rhs.data[i]){
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

void PrintTo(const Message &m, ::std::ostream *os) {
    *os << "Message <Type:" << MessageTypeStr[(int)m.type]
    << " SenderActionType:"<< ActionTypeStr[(int)m.sender_action_type]
    << " CommId:"<< (int)m.communication_id
    << " Data: ";
    for(int i = 0; i < (int)MessageField::ENUM_COUNT; i++){
        *os << m.data[i];
        if(i != (int)MessageField::ENUM_COUNT-1){
            *os << ", ";
        }
    }
    *os << ">";
}

#endif //TESTING