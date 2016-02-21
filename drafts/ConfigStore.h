//
// Created by cyberxix on 16.02.16.
//

#ifndef GEARRAKE_CONFIGSTORE_H
#define GEARRAKE_CONFIGSTORE_H

#include "constants.h"
class EepromWrapper;

class ConfigStore {
public:
    static int getTimeoutValue(CylinderPosition position);
    static void  setTimeout(CylinderPosition position, int value);
    static int getTimerValue(Timing timing);
    static void  setTimer(Timing timing, int value);
private:
    static EepromWrapper* ee;
};

class EepromWrapper {
public:
    //Functionality to 'get' and 'put' objects to and from EEPROM.
    int get( int idx);
    void put(int idx, const int t);
private:
#ifdef TESTING
    int dummyEeprom[(int)EepromConfig::MAX_TIMEOUTS + (int)EepromConfig::TIMING_ADDRESS];
#endif
};

#endif //GEARRAKE_CONFIGSTORE_H
