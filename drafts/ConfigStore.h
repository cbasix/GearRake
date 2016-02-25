//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_CONFIGSTORE_H
#define GEARRAKE_CONFIGSTORE_H

#include "constants.h"
#include "wrapper.h"

class ConfigStore {
public:
    static int getTimeoutValue(CylinderPosition position);
    static void  setTimeout(CylinderPosition position, int value);
    static int getTimerValue(Timing timing);
    static void  setTimer(Timing timing, int value);
private:
    static EepromWrapper* ee;
};



#endif //GEARRAKE_CONFIGSTORE_H
