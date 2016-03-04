//
// Created by cyberxix on 25.02.16.
//

#ifndef GEARRAKE_SPINNERBACK_H
#define GEARRAKE_SPINNERBACK_H

#include "constants.h"
#include <interfaces.h>

class SpinnerRear : public Cylinder{
public:
    SpinnerRear();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool up;
};


#endif //GEARRAKE_SPINNERBACK_H
