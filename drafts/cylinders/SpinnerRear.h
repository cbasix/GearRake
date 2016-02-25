//
// Created by cyberxix on 25.02.16.
//

#ifndef GEARRAKE_SPINNERBACK_H
#define GEARRAKE_SPINNERBACK_H

#include <constants.h>
#include <interfaces.h>

class SpinnerRear : public Cylinder{
public:
    SpinnerRear();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);
    OutputId getOutputId(CylinderDirection direction);

    virtual bool downNeedsPressure();

private:
    IOState up;
};


#endif //GEARRAKE_SPINNERBACK_H
