//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERTELELEFT_H
#define GEARRAKE_SPINNERTELELEFT_H


#include <interfaces.h>

class SpinnerTeleLeft : public Cylinder{
public:
    SpinnerTeleLeft();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool tele_out;
    bool tele_in;
};


#endif //GEARRAKE_SPINNERTELELEFT_H
