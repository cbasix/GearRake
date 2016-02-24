//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_FRAMELOCK_H
#define GEARRAKE_FRAMELOCK_H


#include <interfaces.h>

class FrameLock : public Cylinder{
public:
    FrameLock();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);

private:
    IOState frame_lock_open;
    IOState frame_lock_closed;
};


#endif //GEARRAKE_FRAMELOCK_H
