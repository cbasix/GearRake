//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MOVE_H
#define GEARRAKE_MOVE_H

#include "interfaces.h"

class MovePosition : public Consumer{
public:
    MovePosition(Controller* c, int parent_communication_id, CylinderId cylinder, CylinderPosition position);

    //inherited:
    virtual ActionType getType();
    virtual void onMessage(Controller* c, Message* m);
private:
    CylinderDirection direction;
    CylinderPosition position;
    CylinderId cylinder;
    int parent_communication_id;
    int communication_id;
    bool is_frame_down;
    bool high_level;
};
class MoveDirection : public Consumer{
public:
    MoveDirection(Controller* c, int parent_communication_id, CylinderId cylinder, CylinderDirection direction, bool instant_quit);

    //inherited:
    virtual ActionType getType();
    virtual void onMessage(Controller* c, Message* m);
private:
    CylinderDirection direction;
    CylinderPosition position;
    CylinderId cylinder;
    int parent_communication_id;
    int communication_id;
};
class MoveTime : public Consumer{
public:
    MoveTime(Controller* c, int parent_communication_id, CylinderId cylinder, CylinderDirection direction, Timing timer);

    //inherited:
    virtual ActionType getType();
    virtual void onMessage(Controller* c, Message* m);
private:
    CylinderDirection direction;
    CylinderPosition position;
    CylinderId cylinder;
    int parent_communication_id;
    int communication_id;
};


#endif //GEARRAKE_MOVE_H
