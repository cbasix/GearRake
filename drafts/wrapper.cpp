//
// Created by cyberxix on 24.02.16.
//
#include "constants.h"
#include "wrapper.h"
#ifndef TESTING
    #include "Arduino.h"
#endif


ExpanderWrapper::ExpanderWrapper(int address) {
#ifndef TESTING
    exp =  Adafruit_MCP23017();
    exp->begin(address);
#endif //TESTING
}



#ifdef TESTING //only usable in test mode
unsigned long ClockWrapper::retv = 0;

void ClockWrapper::setReturnValue(unsigned long retv_){
    retv = retv_;
}
#endif


unsigned long ClockWrapper::getTime() {
#ifdef TESTING
    return retv;
#endif
#ifndef TESTING
    return millis();
#endif
}