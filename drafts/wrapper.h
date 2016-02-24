//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WRAPPER_H
#define GEARRAKE_WRAPPER_H

#include "constants.h"

class ExpanderWrapper{
public:
    ExpanderWrapper(int address);

private:
#ifndef TESTING
    Adafruit_MCP23017 exp;
#endif //TESTING

};


class ClockWrapper{
public:
    static unsigned long getTime();
#ifdef TESTING
    static void setReturnValue(unsigned long retv);

private:
    static unsigned long retv;
#endif

};


#endif //GEARRAKE_WRAPPER_H
