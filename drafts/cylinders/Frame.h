//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_FRAME_H
#define GEARRAKE_FRAME_H


#include <interfaces.h>

class Frame : public Cylinder{

public:
    Frame();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool frame_up;
    bool frame_middle;
    bool frame_low;
    bool frame_ground;
};


#endif //GEARRAKE_FRAME_H
