//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERRIGHT_H
#define GEARRAKE_SPINNERRIGHT_H


#include <interfaces.h>

class SpinnerRight : public Cylinder{
public:
    SpinnerRight();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);

private:
    IOState right_third;
    IOState right_up;
};



#endif //GEARRAKE_SPINNERRIGHT_H
