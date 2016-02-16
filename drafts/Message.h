//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MESSAGE_H
#define GEARRAKE_MESSAGE_H

#include "interfaces.h"
#include "constants_message.h"

class Message {
private:
    int type;
    int communication_id;
    int data[5];
public:
    int getType();
    int getCommunicationId();
    int getValue(int value_descriptor);

    static int generateCommunicationId();
    static int next_generated_communication_id;


    static int createTimeoutRequest(Controller c, ActionType type, int timeout);
    static void createTimeoutRequest(Controller c, ActionType type, int timeout_communication_id, int timeout);

    static int createTimerRequest(Controller c, ActionType type, int stop_after);
    static void createTimerRequest(Controller c, ActionType type, int timeout_communication_id, int stop_after);

    static int createCylinderRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction);
    static void createCylinderRequest(Controller c, ActionType type, int timeout_communication_id, Cylinder cylinder,
                                      CylinderDirection direction);

    static int createMoveTimeRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction, int timer);
    static void createMoveTimeRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder, CylinderDirection direction, int timer);

    static int createMovePositonRequest(Controller c, ActionType type, Cylinder cylinder, CylinderPosition position);
    static void createMovePositonRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder, CylinderPosition position);

    static int createMoveDirectionRequest(Controller c, ActionType type, Cylinder cylinder, CylinderDirection direction);
    static void createMoveDirectionRequest(Controller c, ActionType type, int communication_id, Cylinder cylinder, CylinderDirection direction);


    static void createActionState(Controller c, ActionType type, int parent_communication_id, ActionState state);
    static void createTimeout(Controller c, ActionType type, int parent_communication_id);
    static void createTimerState(Controller c, ActionType type, int parent_communication_id);


};


#endif //GEARRAKE_MESSAGE_H
