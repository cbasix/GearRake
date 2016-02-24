//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WEELTELERIGHT_H
#define GEARRAKE_WEELTELERIGHT_H


#include <interfaces.h>

class WeelTeleRight : public Cylinder{
public:
    WeelTeleRight();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);

private:
    IOState tele_out;
    IOState tele_in;
};

#endif //GEARRAKE_WEELTELERIGHT_H
