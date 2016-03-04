//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WEELTELELEFT_H
#define GEARRAKE_WEELTELELEFT_H


#include <interfaces.h>

class WeelTeleLeft : public Cylinder{
public:
    WeelTeleLeft();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool tele_out;
    bool tele_in;
};

#endif //GEARRAKE_WEELTELELEFT_H
