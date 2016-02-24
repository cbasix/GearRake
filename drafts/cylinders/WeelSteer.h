//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WEELSTEER_H
#define GEARRAKE_WEELSTEER_H


#include <interfaces.h>

class WeelSteer : public Cylinder{
public:
    WeelSteer();
    virtual CylinderPosition getPosition();
    virtual void update(SensorInputId id, IOState value);

private:
    IOState middle;
};


#endif //GEARRAKE_WEELSTEER_H
