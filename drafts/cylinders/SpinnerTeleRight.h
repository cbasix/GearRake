//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERTELERIGHT_H
#define GEARRAKE_SPINNERTELERIGHT_H

#include <interfaces.h>

class SpinnerTeleRight : public Cylinder{
public:
    SpinnerTeleRight();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool tele_out;
    bool tele_in;
};


#endif //GEARRAKE_SPINNERTELERIGHT_H
