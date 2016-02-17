//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MOVE_H
#define GEARRAKE_MOVE_H

#include "interfaces.h"

class MovePosition : public Consumer{
public:
    MovePosition(Controller* c, int parent_communication_id, Cylinder cylinder, CylinderPosition position);

    //inherited:
    virtual ActionType getType();
    virtual void onMessage(Controller* c, Message* m);
private:
    CylinderDirection direction;
    CylinderPosition position;
    Cylinder cylinder;
    int parent_communication_id;
    int communication_id;
};
class MoveDirection : public Consumer{
public:
    MoveDirection(Controller* c, Cylinder cylinder, CylinderDirection direction, int parent_communication_id);

    //inherited:
    virtual ActionType getType();
    virtual void onMessage(Controller* c, Message* m);
private:
    CylinderDirection direction;
    CylinderPosition position;
    Cylinder cylinder;
    int parent_communication_id;
    int communication_id;
};
class MoveTime : public Consumer{
public:
    MoveTime(Controller* c, int parent_communication_id, Cylinder cylinder, CylinderDirection direction, int stop_after_timer);

    //inherited:
    virtual ActionType getType();
    virtual void onMessage(Controller* c, Message* m);
private:
    CylinderDirection direction;
    CylinderPosition position;
    Cylinder cylinder;
    int parent_communication_id;
    int communication_id;
};


#endif //GEARRAKE_MOVE_H
