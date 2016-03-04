//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WEELTELERIGHT_H
#define GEARRAKE_WEELTELERIGHT_H


#include <interfaces.h>

class WeelTeleRight : public Cylinder{
public:
    WeelTeleRight();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool tele_out;
    bool tele_in;
};

#endif //GEARRAKE_WEELTELERIGHT_H
