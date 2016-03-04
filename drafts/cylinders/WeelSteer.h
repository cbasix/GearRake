//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WEELSTEER_H
#define GEARRAKE_WEELSTEER_H


#include <interfaces.h>

class WeelSteer : public Cylinder{
public:
    WeelSteer();
    CylinderPosition getPosition();
    void update(SensorInputId id, bool value);
    OutputId getOutputId(CylinderDirection direction);

    bool downNeedsPressure();

private:
    bool middle;
};


#endif //GEARRAKE_WEELSTEER_H
