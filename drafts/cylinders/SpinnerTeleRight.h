//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERTELERIGHT_H
#define GEARRAKE_SPINNERTELERIGHT_H

#include <interfaces.h>

class SpinnerTeleRight : public Cylinder{
public:
    SpinnerTeleRight();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);

private:
    IOState tele_out;
    IOState tele_in;
};


#endif //GEARRAKE_SPINNERTELERIGHT_H
