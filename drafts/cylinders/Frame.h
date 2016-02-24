//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_FRAME_H
#define GEARRAKE_FRAME_H


#include <interfaces.h>

class Frame : public Cylinder{

public:
    Frame();
    virtual CylinderPosition getPosition();

    virtual void update(SensorInputId id, IOState value);

private:
    IOState frame_up;
    IOState frame_middle;
    IOState frame_low;
    IOState frame_ground;
};


#endif //GEARRAKE_FRAME_H
