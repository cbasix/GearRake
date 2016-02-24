//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WEELTELELEFT_H
#define GEARRAKE_WEELTELELEFT_H


#include <interfaces.h>

class WeelTeleLeft : public Cylinder{
public:
    WeelTeleLeft();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);

private:
    IOState tele_out;
    IOState tele_in;
};

#endif //GEARRAKE_WEELTELELEFT_H
