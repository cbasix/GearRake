//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_CONFIGSTORE_H
#define GEARRAKE_CONFIGSTORE_H

#include "constants.h"

class ConfigStore {
public:
    static int getTimeout(CylinderPosition position);
    static int getTimer(Timing timing);

};


#endif //GEARRAKE_CONFIGSTORE_H
