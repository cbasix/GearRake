//
// Created by cyberxix on 16.02.16.
//
#include "constants.h"
#include "interfaces.h"
#include "ConfigStore.h"

EepromWrapper* ConfigStore::ee = new EepromWrapper();

int ConfigStore::getTimeoutValue(CylinderPosition position) {
    return ee->get((int)EepromConfig::TIMEOUT_ADDRESS + (int)position);
}

int ConfigStore::getTimerValue(Timing timing) {
    return ee->get((int)EepromConfig::TIMING_ADDRESS + (int)timing);
}

void ConfigStore::setTimeout(CylinderPosition position, int value) {
    return ee->put((int)EepromConfig::TIMEOUT_ADDRESS + (int)position, value);
}

void ConfigStore::setTimer(Timing timing, int value) {
    ee->put((int)EepromConfig::TIMING_ADDRESS + (int)timing, value);
}


int EepromWrapper::get(int idx) {
#ifdef TESTING
    return dummyEeprom[idx];
#endif //testing
#ifndef TESTING
    int t;
    int addr = idx * (int)sizeof(int)
    EEPROM.get(idx, t)
    return t;
#endif //testing
}

void EepromWrapper::put(int idx, const int t) {
#ifdef TESTING
    dummyEeprom[idx] = t;
#endif //testing
#ifndef TESTING
    int addr = idx * (int)sizeof(int)
    return EEPROM.put(idx, t)
#endif //testing
}

