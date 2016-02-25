//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_CYLINDERPOSITION_H
#define GEARRAKE_CYLINDERPOSITION_H


#include <interfaces.h>
#include "constants.h"

class Position : public Consumer{
public:
    Position(Cylinder* cylinder[], int cyl_len);
    virtual ActionType getType();
    virtual void onMessage(Controller *c, Message *m);

private:
    Cylinder* cylinders[];
    CylinderPosition cylinder_pos[(int) CylinderId::ENUM_COUNT];
    int cyl_len;
};

#endif //GEARRAKE_CYLINDERPOSITION_H
