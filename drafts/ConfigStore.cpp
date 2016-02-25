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


