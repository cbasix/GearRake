//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MESSAGE_H
#define GEARRAKE_MESSAGE_H


#include <iostream>
#include "interfaces.h"
#include "constants.h"
#include "constants_message.h"
#include "constants_io.h"

class Controller;

class Message {
private:
    ActionType sender_action_type;
    MessageType type;
    int communication_id;
public:
    void setCommunicationId(int communication_id) ;
    void setSenderActionType(const ActionType &sender_action_type);
    void setType(const MessageType &type);

private:
    int data[(int)MessageField::ENUM_COUNT];
    static int next_generated_communication_id;
public:
#ifdef TESTING
    //std::ostream &operator<<(std::ostream &o);
    //void PrintTo(::std::ostream* os);
    friend void PrintTo(const Message &m, ::std::ostream *os);
    bool operator==(const Message& rhs);
#endif
    Message(MessageType type=MessageType::NONE , ActionType sender_action_type=ActionType::NONE , int communication_id=0);
    MessageType getType();
    ActionType getSenderActionType();
    int getCommunicationId();
    int getValue(MessageField field);
    void setValue(MessageField field, int value);

    static int generateCommunicationId();
    //requests
    //static int createTimeoutRequest(Controller* c, ActionType type, int timeout);
    static void createTimeoutRequest(Controller* c, ActionType type, int timeout_communication_id, int timeout);

    //static int createTimerRequest(Controller* c, ActionType type, Timing timer);
    static void createTimerRequest(Controller* c, ActionType type, int timeout_communication_id, Timing timer);

    //static int createCylinderRequest(Controller* c, ActionType type, CylinderId cylinder, CylinderDirection direction);
    static void createCylinderRequest(Controller* c, ActionType type, int timeout_communication_id, CylinderId cylinder,
                                      CylinderDirection direction);

    //static int createMoveTimeRequest(Controller* c, ActionType type, CylinderId cylinder, CylinderDirection direction, int timer);
    static void createMoveTimeRequest(Controller* c, ActionType type, int communication_id, CylinderId cylinder, CylinderDirection direction, Timing timing);

    //static int createMovePositionRequest(Controller* c, ActionType type, CylinderId cylinder, CylinderPosition position);
    static void createMovePositionRequest(Controller* c, ActionType type, int communication_id, CylinderId cylinder, CylinderPosition position);

    //static int createMoveDirectionRequest(Controller* c, ActionType type, CylinderId cylinder, CylinderDirection direction);
    static void createMoveDirectionRequest(Controller* c, ActionType type, int communication_id, CylinderId cylinder, CylinderDirection direction);

    //static int createPositionRequest(Controller* c, ActionType type, CylinderId cylinder);
    static void createPositionRequest(Controller* c, ActionType type, int communication_id, CylinderId cylinder);

    //static int createLedRequest(Controller* c, ActionType type, OutputId led_id, IOState state);
    static void createLedRequest(Controller* c, ActionType type, int communication_id, OutputId led_id, IOState state);

    //static void createActionRequest(Controller c, ActionType type, int communication_id, ActionType recipient, ActionState::);


    //answers
    static void createActionState(Controller* c, ActionType type, int parent_communication_id, ActionState state);
    static void createTimeout(Controller* c, ActionType type, int parent_communication_id, int status);
    static void createTimerState(Controller* c, ActionType type, int parent_communication_id);
    static void createPositionState(Controller* c, ActionType type, int parent_communication_id, CylinderId cylinder, CylinderPosition position);

    //producers
    static void createPositionChange(Controller* c, ActionType type, int parent_communication_id, CylinderId cylinder, CylinderPosition position);
    static void createInputChange(Controller* c, ActionType type, int parent_communication_id, ManualInputId input_id, IOState input_state);



};
//std::ostream &operator<<(std::iostream &o, const Message& rhs);
void PrintTo(const Message& m, ::std::ostream* os);
#endif //GEARRAKE_MESSAGE_H
