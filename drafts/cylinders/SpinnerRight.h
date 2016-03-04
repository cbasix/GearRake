//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_SPINNERRIGHT_H
#define GEARRAKE_SPINNERRIGHT_H


#include <interfaces.h>

class SpinnerRight : public Cylinder{
public:
    SpinnerRight();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool right_third;
    bool right_up;
};



#endif //GEARRAKE_SPINNERRIGHT_H
