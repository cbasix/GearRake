//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_FRAMELOCK_H
#define GEARRAKE_FRAMELOCK_H


#include <interfaces.h>

class FrameLock : public Cylinder{
public:
    FrameLock();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool frame_lock_open;
    bool frame_lock_closed;
};


#endif //GEARRAKE_FRAMELOCK_H
