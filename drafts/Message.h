//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MESSAGE_H
#define GEARRAKE_MESSAGE_H

#include "interfaces.h"
#include "constants_message.h"

class Message {
private:
    ActionType sender_action_type;
    MessageTypes type;
    int communication_id;
    int data[CONF_MESSAGE_LEN];
public:
    Message();
    MessageTypes getType();
    ActionType getSenderActionType();
    int getCommunicationId();
    int getValue(MessageFields field);
    void setValue(MessageFields field, int value);

    static int generateCommunicationId();
    static int next_generated_communication_id;

    //requests
    static int createTimeoutRequest(Controller c, ActionType type, int timeout);
    static void createTimeoutRequest(Controller c, ActionType type, int timeout_communication_id, int timeout);

    static int createTimerRequest(Controller c, ActionType type, int stop_after);
    static void createTimerRequest(Controller c, ActionType type, int timeout_communication_id, int stop_after);

    static int createCylinderRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction);
    static void createCylinderRequest(Controller c, ActionType type, int timeout_communication_id, Cylinder cylinder,
                                      CylinderDirection direction);

    static int createMoveTimeRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction, int timer);
    static void createMoveTimeRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder, CylinderDirection direction, int timer);

    static int createMovePositionRequest(Controller c, ActionType type, Cylinder cylinder, CylinderPosition position);
    static void createMovePositionRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder, CylinderPosition position);

    static int createMoveDirectionRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction);
    static void createMoveDirectionRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder, CylinderDirection direction);

    //answers
    static void createActionState(Controller c, ActionType type, int parent_communication_id, ActionState state);
    static void createTimeout(Controller c, ActionType type, int parent_communication_id);
    static void createTimerState(Controller c, ActionType type, int parent_communication_id);

    //producers
    static void createPositionState(Controller c, ActionType type, Cylinder cylinder, CylinderPosition position);


};


#endif //GEARRAKE_MESSAGE_H
