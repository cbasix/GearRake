//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERTELELEFT_H
#define GEARRAKE_SPINNERTELELEFT_H


#include <interfaces.h>

class SpinnerTeleLeft : public Cylinder{
public:
    SpinnerTeleLeft();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);
    OutputId getOutputId(CylinderDirection direction);

    virtual bool downNeedsPressure();

private:
    IOState tele_out;
    IOState tele_in;
};


#endif //GEARRAKE_SPINNERTELELEFT_H
