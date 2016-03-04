//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERLEFT_H
#define GEARRAKE_SPINNERLEFT_H


#include <interfaces.h>

class SpinnerLeft : public Cylinder{
public:
    SpinnerLeft();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool left_third;
    bool left_up;
};


#endif //GEARRAKE_SPINNERLEFT_H
