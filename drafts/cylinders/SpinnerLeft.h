//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERLEFT_H
#define GEARRAKE_SPINNERLEFT_H


#include <interfaces.h>

class SpinnerLeft : public Cylinder{
public:
    SpinnerLeft();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);

private:
    IOState left_third;
    IOState left_up;
};


#endif //GEARRAKE_SPINNERLEFT_H
