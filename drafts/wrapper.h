//
// Created by cyberxix on 24.02.16.
//

#ifndef GEARRAKE_WRAPPER_H
#define GEARRAKE_WRAPPER_H

#include "constants.h"
#ifndef TESTING
    #include Arduino.h
    #include Adafruit_MCP23017.h
#endif

class ExpanderWrapper{
public:
    ExpanderWrapper(int address = 0);
    void digitalWrite(int pin_on_expander, bool state);
    void pinMode(int pin, int mode);

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

class ReadWriteWrapper{
public:
#ifdef TESTING
    static const int W_OUTPUT = 15;
    static const int W_INPUT_PULLUP = 16;
    static const int W_A0 = 87;
#endif
#ifndef TESTING
    static const int W_OUTPUT = OUTPUT
    static const int W_INPUT_PULLUP = INPUT_PULLUP;
    static const int W_A0 = A0;

#endif //Testing
    static void digitalWrite(int pin, bool value);
    static void pinMode(int pin, int mode);
    static bool digitalRead(int pin);
    static int analogRead(int pin);
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


#endif //GEARRAKE_WRAPPER_H
