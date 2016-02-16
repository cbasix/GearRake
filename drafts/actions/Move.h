//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_MOVE_H
#define GEARRAKE_MOVE_H

#import "interfaces.h"

class Move : public Consumer{
public:
    Move(Controller c, Cylinder cylinder, CylinderPosition position, CylinderDirection direction, int parent_communication_id, int stop_after_timer);

    //inherited:
    virtual ActionType getType();
    virtual void onMessage(Controller c, Message m);
private:
    CylinderDirection direction;
    CylinderPosition position;
    Cylinder cylinder;
    int parent_communication_id;
    int timeout_communication_id;
    int timer_communication_id;


/*public:


public:

*/
};


#endif //GEARRAKE_MOVE_H
